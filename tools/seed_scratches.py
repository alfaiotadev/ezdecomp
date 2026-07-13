#!/usr/bin/env python3
"""
seed_scratches.py — populate the public issue board with claimable decomp tasks.

For each unmatched (`U`) function it creates a public decomp.me scratch (target
asm + preprocessed context + exact clang-3.9.1 flags baked in, via tools/decompme)
and opens a GitHub issue linking it, labelled `open` / `good-first-function`. A
contributor then iterates the scratch in the browser with any LLM — no binary,
no toolchain — until the diff reads 100%, and links it back on a PR.

MAINTAINER-ONLY: must run where the game binary is staged (the devcontainer's
/workspace), because tools/decompme reads the target bytes to build each scratch.
The public repo, the toolchain, and the scratches never need the binary — only
this seeding step does.

Usage (inside the container, from /workspace):
    GITHUB_TOKEN=<alfaiotadev PAT> python3 tools/seed_scratches.py --limit 10
    # tune: --max-size 200  --repo alfaiotadev/ezdecomp  --dry-run

Idempotent: skips any function whose symbol already appears in an existing issue.
"""
import argparse, json, os, re, subprocess, sys, time, urllib.error, urllib.request

CSV = "data/lcuswitch_functions.csv"
DECOMPME = "tools/decompme"
API = "https://api.github.com"


def eligible_functions(max_size):
    """Small, unmatched, real functions — good starter tasks. Skips compiler
    thunks (never standalone-matchable) and oversized/hard ones."""
    out = []
    with open(CSV) as f:
        next(f)  # header: Address,Quality,Size,Name
        for line in f:
            p = line.rstrip("\n").split(",")
            if len(p) < 4:
                continue
            _, q, size, name = p[0], p[1], p[2], p[3]
            if q != "U" or not name or name.startswith(("_ZThn", "_ZTh")):
                continue
            try:
                b = int(size)
            except ValueError:
                continue
            if 0 < b <= max_size:
                out.append((name, b))
    out.sort(key=lambda t: t[1])  # smallest first
    return out


def gh(method, path, token, body=None):
    req = urllib.request.Request(
        f"{API}{path}", data=json.dumps(body).encode() if body else None, method=method,
        headers={"Authorization": f"Bearer {token}", "Accept": "application/vnd.github+json",
                 "Content-Type": "application/json", "User-Agent": "seed-scratches"})
    return json.load(urllib.request.urlopen(req))


def already_seeded(repo, token):
    """Symbols already present in any issue (open or closed), for dedup."""
    seen, page = set(), 1
    while True:
        try:
            issues = gh("GET", f"/repos/{repo}/issues?state=all&per_page=100&page={page}", token)
        except urllib.error.HTTPError:
            break
        if not issues:
            break
        for it in issues:
            for m in re.findall(r"`(_Z[\w.]+)`", it.get("body") or ""):
                seen.add(m)
        page += 1
    return seen


def demangle(symbol):
    try:
        return subprocess.run(["c++filt", symbol], capture_output=True, text=True).stdout.strip() or symbol
    except Exception:
        return symbol


def make_scratch(symbol):
    """Run tools/decompme, auto-confirm the upload, return the scratch URL or None."""
    try:
        r = subprocess.run([DECOMPME, symbol], input="y\n", capture_output=True, text=True, timeout=180)
    except Exception as e:
        print(f"    decompme error: {e}")
        return None
    m = re.search(r"Direct:\s*(https://decomp\.me/scratch/\S+)", r.stdout)
    if not m:
        print(f"    no scratch URL in output:\n{(r.stdout + r.stderr)[-400:]}")
        return None
    return m.group(1).rstrip("/")


def issue_body(symbol, demangled, size, scratch):
    return (
        f"**Function:** `{demangled}`\n"
        f"**Symbol:** `{symbol}`\n"
        f"**Size:** {size} bytes\n\n"
        f"**decomp.me scratch (start here — no binary/setup needed):**\n{scratch}\n\n"
        f"Iterate the scratch in your browser with any LLM until the diff reads **100%**, "
        f"then open a PR with the source and link the scratch. Comment `/claim` to claim this.\n\n"
        f"See [CONTRIBUTING.md](../blob/main/docs/CONTRIBUTING.md)."
    )


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=10, help="max functions to seed this run")
    ap.add_argument("--max-size", type=int, default=200, help="skip functions larger than this (bytes)")
    ap.add_argument("--repo", default="alfaiotadev/ezdecomp")
    ap.add_argument("--dry-run", action="store_true", help="create scratches but do NOT open issues")
    args = ap.parse_args()

    token = os.environ.get("GITHUB_TOKEN")
    if not token and not args.dry_run:
        sys.exit("set GITHUB_TOKEN (the alfaiotadev PAT)")
    if not os.path.exists(DECOMPME):
        sys.exit(f"{DECOMPME} not found — run this from /workspace in the devcontainer (needs the binary)")

    seen = set() if args.dry_run else already_seeded(args.repo, token)
    print(f"{len(seen)} functions already on the board")
    candidates = [(n, b) for n, b in eligible_functions(args.max_size) if n not in seen]
    print(f"{len(candidates)} eligible U functions ≤{args.max_size}B; seeding up to {args.limit}")

    made = 0
    for symbol, size in candidates:
        if made >= args.limit:
            break
        print(f"[{made+1}/{args.limit}] {symbol} ({size}B)")
        scratch = make_scratch(symbol)
        if not scratch:
            continue
        dm = demangle(symbol)
        if args.dry_run:
            print(f"    scratch {scratch}  (dry-run, no issue)")
            made += 1
            continue
        try:
            iss = gh("POST", f"/repos/{args.repo}/issues", token, {
                "title": f"Implement {dm}", "body": issue_body(symbol, dm, size, scratch),
                "labels": ["open", "good-first-function"]})
            print(f"    issue #{iss['number']}  ·  {scratch}")
            made += 1
        except urllib.error.HTTPError as e:
            print(f"    issue create failed: {e.code} {e.read().decode()[:150]}")
        time.sleep(1)  # be gentle on both APIs
    print(f"done — seeded {made} tasks")


if __name__ == "__main__":
    main()
