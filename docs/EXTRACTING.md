# Extracting `main` from your dump

`tools/setup.py` needs the original **`main` NSO** (EU v1.0.3). This repo never
ships it — you extract it from your own legal dump. `tools/extract_main.py`
automates that, natively on arm64 (no Rosetta/qemu). **Run it in the
devcontainer** (or any native arm64 Linux container — on Apple Silicon,
[OrbStack](https://orbstack.dev) runs these without emulation), where the build
deps (OpenSSL, make) are guaranteed. For example, without opening VS Code:

```bash
docker run --rm --platform=linux/arm64 -v "$PWD":/workspace -w /workspace \
  ubuntu:24.04 bash -lc \
  'apt-get update -qq && apt-get install -y -qq build-essential libssl-dev git python3 ca-certificates && tools/extract_main.py'
```

## Layout it expects

```
LEGO_City_Undercover/            (gitignored — your dump)
├── LEGO CITY Undercover [010085500130A000][v0] ... .nsp   # base   (v1.0.0)
├── LEGO CITY Undercover [010085500130A800][v196608] ...nsp # update (v1.0.3)
└── keys/
    ├── prod.keys
    └── title.keys
```

Firmware (`fw/Firmware.22.1.0.zip`) is **not** used by extraction — only
`prod.keys` + `title.keys` + the update NSP's ticket are needed.

## Run it

```bash
tools/extract_main.py            # extract + verify sha256 -> LEGO_City_Undercover/main
tools/extract_main.py --setup    # ...and immediately run tools/setup.py
```

What it does:

1. Builds `hactool` from source into `tools/bin/` if missing
   (`tools/fetch_hactool.sh`; native arm64, gitignored).
2. Unpacks the update NSP's PFS0 → NCAs + ticket.
3. Resolves the (encrypted) title key from `title.keys` via the NCAs' rights id.
4. Extracts each NCA's ExeFS and picks out `main`. The ExeFS in a patch NCA is
   the full updated executable (only RomFS is a BKTR delta), so no base-NCA
   merge is needed to get v1.0.3 `main`.
5. Verifies its sha256 against the known EU v1.0.3 hashes
   (compressed `cf65ba20…`, uncompressed `e9cdda9d…`).
6. Copies it to `LEGO_City_Undercover/main` and prints the `setup.py` command.

## Then

```bash
tools/setup.py LEGO_City_Undercover/main   # convert to ELF + create build/
tools/build.py                             # build
tools/check                                # verify matching
```

## Options

`--dump-dir`, `--keys`, `--title-keys`, `--hactool`, `--out`, `--setup`
(see `tools/extract_main.py --help`).

## Notes

- Keys and the dump are secrets/copyrighted and stay gitignored — never commit
  them (AGENTS.md §2).
- If the sha256 does not match, you likely dumped a different region/version;
  the target is **EU v1.0.3**.
