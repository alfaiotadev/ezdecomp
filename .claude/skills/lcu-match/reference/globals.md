# Identifying unnamed `.data`/`.rodata` globals (unblocking work)

A function that references an unidentified global cannot be reconstructed until
the global has a name. Naming a **shared** global unblocks *every* referencing
function at once — the highest-leverage unblock on the board (GitHub #310).

## The sweep
`tools/leverage/sweep_unnamed_globals.py` disassembles `data/main.elf`, resolves
every `ADRP+ADD` (materialized address) and `ADRP+LDR`-into-`.got` reference
(followed through its `R_AARCH64_RELATIVE` relocation to the real target), drops
anything already in `data/data_symbols.csv`, and ranks the rest by number of
distinct referencing functions.

```bash
python3 tools/leverage/sweep_unnamed_globals.py --top 50            # all sections
python3 tools/leverage/sweep_unnamed_globals.py --top 100000 \
    | grep -E '\.data|\.bss'                                        # real globals only
```

Address math: **ELF vaddr = runtime addr − 0x7100000000** (.text at ELF vaddr 0).

## Reading the output
- **`.rodata` hits dominate the raw ranking but are mostly low-value** —
  serialization field-name strings (e.g. `packedInterpolationInfo`) and float
  constant pools. Naming them rarely unblocks anything.
- **`.data`/`.bss` hits are the real blockers** — global instances, static
  tables, and vtables. ~4,500 shared unnamed `.data`/`.bss` targets exist today.
  Work this list top-down.

## Identifying a target once you've picked one
- **Is it a vtable?** Check `objdump -R data/main.elf` for a run of
  `R_AARCH64_RELATIVE` relocs at consecutive 8-byte offsets whose addends point
  **into `.text`** (< 0xd7952c). A block of code pointers = a vtable; name it
  `_ZTV<class>` and its slots become matchable virtuals.
- **Is it a `.got` indirection?** The reloc addend is the real `.data`/`.rodata`
  target — name *that*, not the GOT slot.
- **Worked example (the known blocker):** `_Z20NuMtx24BitCorrectionP5NUMTXPKS_`
  loads GOT slot `0x71020a80d8`, whose `R_AARCH64_RELATIVE` addend is
  `0x71_01ab2d90` — a `.data` const table beginning `1.0f, 0, 0, …` (a matrix).
  Identify that table, add it to `data_symbols.csv`, and the function unblocks.

Add every identification to `data/data_symbols.csv` (`Address,MangledName`,
runtime base `0x7100000000`) so the sweep stops re-surfacing it.
