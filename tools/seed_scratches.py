#!/usr/bin/env python3
"""
seed_scratches.py — populate the public issue board with claimable decomp tasks.

For each selected function it creates a public decomp.me scratch (target asm +
preprocessed context + exact clang-3.9.1 flags baked in, via tools/decompme) and
opens a GitHub issue linking it, labelled `open` / `good-first-function`. A
contributor then iterates the scratch in the browser with any LLM — no binary,
no toolchain — until the diff reads 100%, and links it back on a PR.

IMPORTANT — what tools/decompme can seed:
  tools/decompme deduces a function's source file + context from the DECOMP ELF's
  debug info (i.e. the function must be COMPILED IN). So it works out of the box
  for implemented functions:
    * `m` / `M` (implemented but not byte-matching) — the natural "help make this
      match" task. This is the DEFAULT seed set.
    * `O` (already matching) — only useful for demos.
  It CANNOT deduce context for an untouched `U` function (not in the build) — that
  needs an explicit `-s <context source file>` (see --u-context-source, experimental).

MAINTAINER-ONLY: run where the game binary is staged (the devcontainer /workspace),
because tools/decompme reads the target bytes. Contributors need no binary.

Usage (inside the container, from /workspace):
    GITHUB_TOKEN=<alfaiotadev PAT> python3 tools/seed_scratches.py --limit 10
    # options: --quality m,M  --min-size 16  --max-size 400  --repo alfaiotadev/ezdecomp  --dry-run
    # experimental U seeding: --quality U --u-context-source src/<subsystem>/<file>.cpp

Idempotent: skips any function whose symbol already appears in an existing issue.
"""
import argparse, json, os, re, subprocess, sys, time, urllib.error, urllib.request

CSV = "data/lcuswitch_functions.csv"
DECOMPME = "tools/decompme"
API = "https://api.github.com"


def eligible_functions(qualities, min_size, max_size):
    """Functions matching the requested quality states and size window. Skips
    compiler thunks (never standalone-matchable). Smallest first."""
    out = []
    with open(CSV) as f:
        next(f)  # header: Address,Quality,Size,Name
        for line in f:
            p = line.rstrip("\n").split(",")
            if len(p) < 4:
                continue
            _, q, size, name = p[0], p[1], p[2], p[3]
            # skip compiler thunks and deleting destructors (D0Ev) — decompme can't
            # build a translation unit for them ("failed to get translation unit").
            if q not in qualities or not name or name.startswith(("_ZThn", "_ZTh")) or name.endswith("D0Ev"):
                continue
            try:
                b = int(size)
            except ValueError:
                continue
            if min_size <= b <= max_size:
                out.append((name, b))
    out.sort(key=lambda t: t[1])
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


ANSI = re.compile(r"\x1b\[[0-9;?]*[a-zA-Z]")


def ensure_libclang():
    """decompme uses libclang to move the target function into the scratch's source
    tab (leaving only deps in context) — a much cleaner starting point. Without it
    the function stays in context and the source tab is empty. Point LIBCLANG_PATH
    at any installed libclang if the caller didn't. (Install: apt-get install libclang1-18.)"""
    import glob
    if os.environ.get("LIBCLANG_PATH"):
        return True
    for pat in ("/usr/lib/*/libclang*.so*", "/usr/lib/llvm-*/lib/libclang*.so*",
                "/usr/lib/libclang*.so*", "/usr/local/lib/libclang*.so*"):
        hits = glob.glob(pat)
        if hits:
            os.environ["LIBCLANG_PATH"] = os.path.dirname(hits[0])
            return True
    print("WARNING: libclang not found — scratches will have the function in context, "
          "not the source tab (install libclang1-18 for a cleaner layout)")
    return False


def make_scratch(symbol, u_context_source, timeout=120):
    """Run tools/decompme in a PTY (its upload confirmation REQUIRES a TTY —
    piped stdin fails with 'input device is not a TTY'), auto-answer the prompt,
    and return (scratch_url, None) or (None, error). Must run with cwd=/workspace."""
    import pty, select, signal, time as _t
    cmd = [DECOMPME] + (["-s", u_context_source] if u_context_source else []) + [symbol]
    pid, fd = pty.fork()
    if pid == 0:  # child
        os.execvp(cmd[0], cmd)
        os._exit(127)
    buf, sent, t0 = b"", False, _t.time()
    while True:
        if _t.time() - t0 > timeout:
            try:
                os.kill(pid, signal.SIGKILL)
            except OSError:
                pass
            os.waitpid(pid, 0)
            return None, f"timed out after {timeout}s"
        try:
            r, _, _ = select.select([fd], [], [], 1)
        except OSError:
            break
        if fd in r:
            try:
                d = os.read(fd, 4096)
            except OSError:
                break
            if not d:
                break
            buf += d
            if not sent and b"Upload?" in buf:
                os.write(fd, b"y\n")
                sent = True
    try:
        os.waitpid(pid, 0)
    except OSError:
        pass
    out = ANSI.sub("", buf.decode(errors="replace"))
    m = re.search(r"Direct:\s*(https://decomp\.me/scratch/\S+)", out)
    if not m:
        err = next((ln.strip() for ln in out.splitlines() if "Error:" in ln), "no scratch URL")
        return None, err
    return m.group(1).rstrip("/"), None


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
    ap.add_argument("--limit", type=int, default=10, help="stop after this many issues created")
    ap.add_argument("--quality", default="m,M", help="comma-separated quality states to seed (default: m,M)")
    ap.add_argument("--min-size", type=int, default=16, help="skip functions smaller than this (bytes)")
    ap.add_argument("--max-size", type=int, default=400, help="skip functions larger than this (bytes)")
    ap.add_argument("--u-context-source", help="experimental: context .cpp passed to decompme -s (for --quality U)")
    ap.add_argument("--max-attempts", type=int, default=0, help="cap decompme attempts (default: 3x limit)")
    ap.add_argument("--repo", default="alfaiotadev/ezdecomp")
    ap.add_argument("--dry-run", action="store_true", help="create scratches but do NOT open issues")
    args = ap.parse_args()

    token = os.environ.get("GITHUB_TOKEN")
    if not token and not args.dry_run:
        sys.exit("set GITHUB_TOKEN (the alfaiotadev PAT)")
    if not os.path.exists(DECOMPME):
        sys.exit(f"{DECOMPME} not found — run from /workspace in the devcontainer (needs the binary)")
    ensure_libclang()
    qualities = set(q.strip() for q in args.quality.split(",") if q.strip())
    if "U" in qualities and not args.u_context_source:
        sys.exit("seeding U functions needs --u-context-source <a .cpp with the right includes> "
                 "(decompme can't deduce context for functions not in the build)")
    max_attempts = args.max_attempts or args.limit * 3

    seen = set() if args.dry_run else already_seeded(args.repo, token)
    print(f"{len(seen)} functions already on the board")
    candidates = [(n, b) for n, b in eligible_functions(qualities, args.min_size, args.max_size) if n not in seen]
    print(f"{len(candidates)} eligible {'/'.join(sorted(qualities))} functions "
          f"{args.min_size}-{args.max_size}B; seeding up to {args.limit} (max {max_attempts} attempts)")

    made = attempts = failed = 0
    for symbol, size in candidates:
        if made >= args.limit or attempts >= max_attempts:
            break
        attempts += 1
        print(f"[{attempts}] {symbol} ({size}B)")
        scratch, err = make_scratch(symbol, args.u_context_source)
        if not scratch:
            failed += 1
            print(f"    skip: {err}")
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
            failed += 1
            print(f"    issue create failed: {e.code} {e.read().decode()[:150]}")
        time.sleep(1)
    print(f"done — seeded {made}, attempted {attempts}, failed {failed}")
    if made == 0 and failed:
        print("all attempts failed — if seeding U, decompme needs implemented functions or a valid "
              "--u-context-source; try --quality m,M first.")


if __name__ == "__main__":
    main()
