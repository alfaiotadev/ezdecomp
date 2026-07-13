#!/usr/bin/env python3
"""Extract the LCU `main` NSO (EU v1.0.3) from the local NSP dump.

Pipeline (all native arm64 — no Rosetta/qemu; run it in the devcontainer):

  1. Build hactool if needed (tools/fetch_hactool.sh).
  2. Unpack the update NSP's PFS0 -> NCAs + ticket.
  3. Derive the (encrypted) title key from title.keys via the NCAs' rights id.
  4. Extract each NCA's ExeFS; the program NCA yields `main`.
  5. Verify sha256 against the known EU v1.0.3 hashes.
  6. Copy `main` next to the dump and print the setup.py command.

The `main` in a patch NCA's ExeFS is the FULL updated executable (ExeFS is not a
BKTR delta — only RomFS is), so no base NCA merge is needed to get v1.0.3 `main`.

Keys and the game dump are never committed (clean-room). Firmware is not used.
"""

import argparse
import hashlib
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

# From tools/setup.py — the accepted EU v1.0.3 `main` NSO hashes.
COMPRESSED_HASH = "cf65ba2016505d83b9a0622704521651566b87510e60ebe0d4413546f2ea59c1"
UNCOMPRESSED_HASH = "e9cdda9d68e30ce797c6cdf32a71ef8fe1eab269e4280a21cd5acd27611d70c8"

RIGHTS_ID_RE = re.compile(r"Rights ID:\s*([0-9a-fA-F]{32})")


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def run(cmd, **kw):
    return subprocess.run(cmd, text=True, capture_output=True, **kw)


def ensure_hactool(explicit: Path | None) -> Path:
    if explicit:
        if not explicit.is_file():
            sys.exit(f"hactool not found at {explicit}")
        return explicit
    found = shutil.which("hactool")
    if found:
        return Path(found)
    local = REPO_ROOT / "tools" / "bin" / "hactool"
    if not local.is_file():
        print(">>> hactool not found; building via tools/fetch_hactool.sh ...")
        subprocess.check_call(["bash", str(REPO_ROOT / "tools" / "fetch_hactool.sh")])
    if not local.is_file():
        sys.exit("failed to obtain hactool")
    return local


def find_nsp(dump_dir: Path, marker: str) -> Path | None:
    cands = sorted(p for p in dump_dir.glob("*.nsp") if marker in p.name)
    return cands[0] if cands else None


def sanitize_keyset(src: Path, dst: Path) -> Path:
    """Write a copy of prod.keys keeping only well-formed 16/32-byte hex keys.

    Modern prod.keys (firmware 22.x) contain newer entries — e.g. 17-byte
    `mariko_master_kek_source_*` / `master_kek_source_06+` — that old hactool
    rejects ("must be 32 hex digits"), which aborts key loading. Dropping them
    is harmless here: LCU is a master-key-0 title, so the keys it needs
    (master_key_00, header_key, titlekek_00, key_area_key_application_00, …)
    are all standard-length and preserved.
    """
    with dst.open("w") as out:
        for line in src.read_text(errors="ignore").splitlines():
            s = line.strip()
            if not s or "=" not in s:
                continue
            name, val = (x.strip() for x in s.split("=", 1))
            val = val.split()[0].lower() if val else ""
            if re.fullmatch(r"[0-9a-f]{32}", val) or re.fullmatch(r"[0-9a-f]{64}", val):
                out.write(f"{name} = {val}\n")
    return dst


def load_title_keys(path: Path) -> dict:
    keys = {}
    for line in path.read_text(errors="ignore").splitlines():
        line = line.strip()
        if not line or line.startswith(("#", ";")) or "=" not in line:
            continue
        rid, key = (x.strip().lower() for x in line.split("=", 1))
        rid = rid.replace("0x", "")
        key = key.split()[0] if key else key
        if len(rid) == 32:
            keys[rid] = key
    return keys


def nca_rights_id(hactool: Path, prod_keys: Path, nca: Path) -> str | None:
    r = run([str(hactool), "-k", str(prod_keys), "-t", "nca",
             "--disablekeywarns", str(nca)])
    m = RIGHTS_ID_RE.search(r.stdout + r.stderr)
    if not m:
        return None
    rid = m.group(1).lower()
    return None if rid == "0" * 32 else rid


def extract_main(hactool: Path, prod_keys: Path, title_key: str | None,
                 ncas: list[Path], work: Path) -> Path | None:
    for i, nca in enumerate(ncas):
        exefs = work / f"exefs_{i}"
        exefs.mkdir(parents=True, exist_ok=True)
        cmd = [str(hactool), "-k", str(prod_keys), "-t", "nca",
               "--disablekeywarns", f"--exefsdir={exefs}"]
        if title_key:
            cmd.append(f"--titlekey={title_key}")
        cmd.append(str(nca))
        run(cmd)  # exefs-only; romfs (bktr) is not requested, so no base needed
        cand = exefs / "main"
        if cand.is_file() and cand.stat().st_size > 0:
            return cand
    return None


def main() -> None:
    ap = argparse.ArgumentParser(description="Extract LCU main NSO from the NSP dump")
    ap.add_argument("--dump-dir", type=Path, default=REPO_ROOT / "LEGO_City_Undercover")
    ap.add_argument("--keys", type=Path, help="prod.keys (default: <dump>/keys/prod.keys)")
    ap.add_argument("--title-keys", type=Path, help="title.keys (default: <dump>/keys/title.keys)")
    ap.add_argument("--hactool", type=Path, help="path to hactool (default: auto/build)")
    ap.add_argument("--out", type=Path, help="output path for main (default: <dump>/main)")
    ap.add_argument("--setup", action="store_true", help="run tools/setup.py <main> on success")
    args = ap.parse_args()

    dump = args.dump_dir
    prod_keys = args.keys or dump / "keys" / "prod.keys"
    title_keys = args.title_keys or dump / "keys" / "title.keys"
    out = args.out or dump / "main"

    for p, what in [(dump, "dump dir"), (prod_keys, "prod.keys"), (title_keys, "title.keys")]:
        if not p.exists():
            sys.exit(f"missing {what}: {p}")

    hactool = ensure_hactool(args.hactool)

    # v1.0.3 lives in the update NSP (...A800). Base (...A000) is v1.0.0.
    nsp = find_nsp(dump, "A800") or find_nsp(dump, "A000")
    if not nsp:
        sys.exit(f"no .nsp found in {dump}")
    print(f">>> Using NSP: {nsp.name}")

    with tempfile.TemporaryDirectory(dir=dump) as td:
        work = Path(td)
        ncas_dir = work / "pfs0"
        ncas_dir.mkdir()

        # hactool chokes on newer key entries; feed it a sanitized keyset.
        keyset = sanitize_keyset(prod_keys, work / "prod.sanitized.keys")

        print(">>> Unpacking PFS0 (NCAs + ticket)...")
        r = run([str(hactool), "-t", "pfs0", f"--outdir={ncas_dir}", str(nsp)])
        if r.returncode != 0 and not any(ncas_dir.glob("*.nca")):
            sys.exit(f"pfs0 unpack failed:\n{r.stderr}")

        ncas = sorted(ncas_dir.glob("*.nca"))
        if not ncas:
            sys.exit("no NCAs found inside the NSP")
        print(f">>> {len(ncas)} NCA(s) extracted")

        # The (encrypted) title key. Prefer reading it straight from the ticket
        # in the NSP — deterministic, no dependence on tool output parsing.
        # Switch tickets use RSA-2048 sig (data at 0x140): encrypted title key
        # at 0x180 (16 bytes), rights id at 0x2A0 (16 bytes).
        title_key = None
        rid = None
        tiks = sorted(ncas_dir.glob("*.tik"))
        if tiks:
            data = tiks[0].read_bytes()
            if len(data) >= 0x2B0:
                enc = data[0x180:0x190]
                rid = data[0x2A0:0x2B0].hex()
                if enc != b"\x00" * 16:
                    title_key = enc.hex()
                    print(f">>> Title key read from ticket {tiks[0].name} (rights id {rid})")
        if not title_key:
            # Fall back: derive the rights id from an NCA, look up title.keys.
            for nca in ncas:
                rid = nca_rights_id(hactool, keyset, nca) or rid
                if rid:
                    break
            if rid and rid != "0" * 32:
                title_key = load_title_keys(title_keys).get(rid)
                if title_key:
                    print(f">>> Title key resolved from title.keys (rights id {rid})")
        if not title_key:
            print(">>> No title key found; attempting standard crypto")

        print(">>> Extracting ExeFS and locating `main`...")
        main_nso = extract_main(hactool, keyset, title_key, ncas, work)
        if not main_nso:
            sys.exit("could not find `main` in any NCA's ExeFS "
                     "(wrong NSP/keys, or unexpected layout)")

        digest = sha256(main_nso)
        if digest == COMPRESSED_HASH:
            print(">>> sha256 OK (compressed NSO) — matches EU v1.0.3")
        elif digest == UNCOMPRESSED_HASH:
            print(">>> sha256 OK (uncompressed NSO) — matches EU v1.0.3")
        else:
            print(f"!!! WARNING: sha256 {digest}\n"
                  f"    does not match the known EU v1.0.3 hashes.\n"
                  f"    Expected {COMPRESSED_HASH} (compressed)\n"
                  f"          or {UNCOMPRESSED_HASH} (uncompressed).\n"
                  f"    Extracted anyway — verify you dumped the EU v1.0.3 update.")

        out.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(main_nso, out)
        print(f">>> Wrote: {out}")

    if args.setup:
        print(">>> Running tools/setup.py ...")
        subprocess.check_call([sys.executable, str(REPO_ROOT / "tools" / "setup.py"), str(out)])
    else:
        print(f"\nNext: tools/setup.py {out}")


if __name__ == "__main__":
    main()
