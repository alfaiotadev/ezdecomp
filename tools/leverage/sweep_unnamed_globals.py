#!/usr/bin/env python3
"""Leverage issue #310 — find shared, still-unnamed .data/.rodata/.bss globals.

For every function in data/lcuswitch_functions.csv, resolve the data addresses it
references and rank the ones NOT yet in data/data_symbols.csv by how many distinct
functions touch them. A global referenced by many functions is the highest-value
thing to identify: naming it unblocks every referrer at once.

Two reference forms are resolved:
  * ADRP+ADD            -> a directly materialized address (global / string / const)
  * ADRP+LDR into .got  -> the GOT slot is followed through its R_AARCH64_RELATIVE
                           relocation to the real target it points at.

Register liveness is tracked so a stale ADRP page in a reused register does not
produce false hits (the base register's page is cleared whenever any instruction
overwrites it).

Static-analysis only; runs on the host. ELF vaddr == runtime addr - 0x7100000000.

    python3 tools/leverage/sweep_unnamed_globals.py [--top N] [--min-refs K]
"""
import argparse
import bisect
import csv
import re
import subprocess
from collections import defaultdict

ELF = "data/main.elf"
BASE = 0x7100000000
FUNCS_CSV = "data/lcuswitch_functions.csv"
DATA_CSV = "data/data_symbols.csv"

# ELF-vaddr section bounds (from `r2 -c iS`), offset space.
RODATA_LO, RODATA_HI = 0x00D7A000, 0x01A525F6
DATA_LO = 0x01A53000
GOT_LO, GOT_HI = 0x0209B168, 0x020B7FF0
GOTPLT_LO, GOTPLT_HI = 0x0209A830, 0x0209B168
BSS_HI = 0x025E1000
TEXT_HI = 0x00D7952C  # end of .text — reloc targets below this are code

ADRP_RE = re.compile(r"^\s+[0-9a-f]+:\s+[0-9a-f]{8}\s+adrp\s+(x\d+), (0x[0-9a-f]+)")
ADD_RE = re.compile(r"^\s+([0-9a-f]+):\s+[0-9a-f]{8}\s+add\s+(x\d+), (x\d+), #(0x[0-9a-f]+)")
LDR_RE = re.compile(r"^\s+([0-9a-f]+):\s+[0-9a-f]{8}\s+ldr\s+[wxsdq]\d+, \[(x\d+)(?:, #(0x[0-9a-f]+))?\]")
# destination register of any instruction (to invalidate stale pages).
# Matches w- and x-forms; w<N> aliases x<N>, so both must clear x<N>.
DST_RE = re.compile(r"^\s+[0-9a-f]+:\s+[0-9a-f]{8}\s+\S+\s+[wx](\d+)")


def section(off):
    if off < TEXT_HI:
        return ".text(code)"
    if RODATA_LO <= off < RODATA_HI:
        return ".rodata"
    if DATA_LO <= off < GOTPLT_LO:
        return ".data"
    if GOTPLT_LO <= off < GOT_HI:
        return ".got"
    if off < BSS_HI:
        return ".bss"
    return "?"


def load_funcs():
    recs = []
    with open(FUNCS_CSV) as f:
        for row in csv.reader(f):
            if len(row) < 4 or row[0] == "Address":
                continue
            a = int(row[0], 16) - BASE
            recs.append((a, a + int(row[2]), row[1], row[3]))
    recs.sort()
    return [r[0] for r in recs], recs


def load_named():
    named = set()
    with open(DATA_CSV) as f:
        for row in csv.reader(f):
            if row:
                try:
                    named.add(int(row[0], 16) - BASE)
                except ValueError:
                    pass
    return named


def load_got_relocs():
    """GOT/data slot offset -> target offset (R_AARCH64_RELATIVE addend)."""
    m = {}
    out = subprocess.run(["objdump", "-R", ELF], capture_output=True, text=True).stdout
    rx = re.compile(r"^([0-9a-f]{16}) R_AARCH64_RELATIVE\s+\*ABS\*\+(0x[0-9a-f]+)")
    for line in out.splitlines():
        mm = rx.match(line)
        if mm:
            m[int(mm.group(1), 16)] = int(mm.group(2), 16)
    return m


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--top", type=int, default=50)
    ap.add_argument("--min-refs", type=int, default=2)
    args = ap.parse_args()

    starts, recs = load_funcs()
    named = load_named()
    got = load_got_relocs()

    def func_at(pc):
        i = bisect.bisect_right(starts, pc) - 1
        if 0 <= i < len(recs) and recs[i][0] <= pc < recs[i][1]:
            return recs[i]
        return None

    # target_off -> set(func_start); plus how many referrers are U
    refs = defaultdict(set)
    ucount = defaultdict(int)

    def hit(pc, target, via_got):
        # follow a GOT slot to the real data it points at
        if via_got and target in got:
            target = got[target]
        if target < TEXT_HI:  # points at code, not a data global
            return
        if not (RODATA_LO <= target < BSS_HI):
            return
        if target in named:
            return
        fn = func_at(pc)
        if fn is None:
            return
        if fn[0] not in refs[target]:
            refs[target].add(fn[0])
            if fn[2] == "U":
                ucount[target] += 1

    proc = subprocess.Popen(["objdump", "-d", ELF], stdout=subprocess.PIPE, text=True)
    page = {}  # reg -> adrp page (only valid until reg is overwritten)
    for line in proc.stdout:
        m = ADD_RE.match(line)
        if m:
            src = m.group(3)
            if src in page:
                hit(int(m.group(1), 16), page[src] + int(m.group(4), 16), False)
            page.pop(m.group(2), None)  # dst now holds full addr, not a page
            continue
        m = LDR_RE.match(line)
        if m:
            src = m.group(2)
            if src in page and m.group(3) is not None:
                hit(int(m.group(1), 16), page[src] + int(m.group(3), 16), True)
            # LDR dst is captured by DST_RE below; fall through to invalidate it
        m2 = ADRP_RE.match(line)
        if m2:
            page[m2.group(1)] = int(m2.group(2), 16)
            continue
        # any other instruction: invalidate the page cached in its dst register
        md = DST_RE.match(line)
        if md:
            page.pop("x" + md.group(1), None)
    proc.wait()

    ranked = sorted(
        refs.items(), key=lambda kv: (len(kv[1]), ucount[kv[0]]), reverse=True
    )
    ranked = [(t, s) for t, s in ranked if len(s) >= args.min_refs]
    print(f"# {len(ranked)} unnamed data targets referenced by >= {args.min_refs} funcs")
    print(f"# (resolved through GOT; code targets & {len(named)} named symbols excluded)")
    print(f"{'runtime_addr':<20}{'refs':>6}{'U':>6}  section")
    for t, s in ranked[: args.top]:
        print(f"0x{t + BASE:016x}  {len(s):>5} {ucount[t]:>5}  {section(t)}")


if __name__ == "__main__":
    main()
