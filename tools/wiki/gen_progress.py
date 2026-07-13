#!/usr/bin/env python3
"""
gen_progress.py — regenerate the decomp progress board for the GitHub wiki.

The board is derived entirely from committed repo state
(`data/lcuswitch_functions.csv`, the authoritative per-function match ledger),
so it can be regenerated deterministically after any function-match merge and
kept in lock-step with `master`.

The per-subsystem breakdown maps each matched symbol to the `src/<subsystem>/`
directory that defines it, using `nm` over the built objects in `build/`. That
requires a prior `tools/build.py`; if `build/` is absent the board is still
generated, just without the subsystem bars (with a note).

Usage:
    tools/wiki/gen_progress.py               # print the markdown to stdout
    tools/wiki/gen_progress.py -o Home.md    # write to a file
    tools/wiki/gen_progress.py --push        # update the wiki Home page via API

--push reads GITHUB_TOKEN / GITHUB_API_URL / GITHUB_OWNER / GITHUB_REPO from
the environment (source .env first). It PATCHes the existing Home page, or
creates it if absent. The token is only ever sent in the Authorization header —
never printed. See AGENTS.md §4 (the board is refreshed as part of the merge
cycle).
"""
import argparse, base64, datetime, glob, json, os, ssl, subprocess, sys, urllib.error, urllib.request
from collections import Counter

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CSV = os.path.join(REPO, "data", "lcuswitch_functions.csv")
CSV_REL = "data/lcuswitch_functions.csv"  # ledger path relative to REPO (for git history)

# Quality codes (AGENTS.md §4): O = verified byte-exact match, M/m = decompiled
# but not yet matching (major/minor diffs), U = untouched.
MATCHED = {"O"}
INPROGRESS = {"M", "m"}


def collect_csv():
    total_n = total_b = o_n = o_b = p_n = p_b = 0
    o_syms = set()
    with open(CSV) as f:
        next(f)  # header: Address,Quality,Size,Name
        for line in f:
            parts = line.rstrip("\n").split(",")
            if len(parts) < 4:
                continue
            _, q, size, name = parts[0], parts[1], parts[2], parts[3]
            try:
                b = int(size)
            except ValueError:
                b = 0
            total_n += 1
            total_b += b
            if q in MATCHED:
                o_n += 1
                o_b += b
                o_syms.add(name)
            elif q in INPROGRESS:
                p_n += 1
                p_b += b
    return dict(total_n=total_n, total_b=total_b, o_n=o_n, o_b=o_b,
                p_n=p_n, p_b=p_b, o_syms=o_syms)


def subsystem_breakdown(o_syms):
    """Map matched symbols to their src/<subsystem>/ dir via nm on built objects.

    Returns (Counter subsystem->count, mapped_total) or (None, 0) if no build.
    """
    objs = glob.glob(os.path.join(REPO, "build/CMakeFiles/lcuswitch.dir/src/**/*.obj"),
                     recursive=True)
    if not objs:
        return None, 0
    counts, seen = Counter(), set()
    for obj in objs:
        rel = obj.split("src/", 1)[1]
        sub = rel.split("/")[0] if "/" in rel else "(root)"
        try:
            out = subprocess.check_output(["nm", "--defined-only", obj],
                                          stderr=subprocess.DEVNULL).decode()
        except Exception:
            continue
        for line in out.splitlines():
            p = line.split()
            if len(p) >= 3 and p[1] in ("T", "t", "W", "w") and p[2] in o_syms and p[2] not in seen:
                seen.add(p[2])
                counts[sub] += 1
    return counts, sum(counts.values())


def bar(frac, width=42):
    n = max(0, min(width, round(frac * width)))
    return "█" * n + "░" * (width - n)


def pct(a, b):
    return (a / b * 100) if b else 0


def sparkline(values):
    lo, hi = min(values), max(values)
    span = (hi - lo) or 1
    blk = "▁▂▃▄▅▆▇█"
    return "".join(blk[min(7, int((v - lo) / span * 7 + 0.5))] for v in values)


def daily_series():
    """Cumulative byte-exact (O) match count per activity-day, reconstructed from
    the git history of the CSV ledger (one sample = the last commit of each day, so
    it's one `git show` per active day, not per commit). A pure function of committed
    git state — no persisted history file — so it never drifts from `master`.
    Returns [(iso_date, delta, cumulative), ...] for days whose O-count changed."""
    try:
        log = subprocess.run(["git", "-C", REPO, "log", "--format=%cs %H", "--", CSV_REL],
                             capture_output=True, text=True).stdout
    except Exception:
        return []
    last_of_day = {}
    for line in log.splitlines():          # newest-first
        parts = line.split(" ", 1)
        if len(parts) == 2:
            last_of_day.setdefault(parts[0], parts[1])   # first seen = last commit that day
    rows, prev = [], 0
    for day in sorted(last_of_day):
        try:
            blob = subprocess.run(["git", "-C", REPO, "show", f"{last_of_day[day]}:{CSV_REL}"],
                                  capture_output=True, text=True).stdout
        except Exception:
            continue
        o = sum(1 for ln in blob.splitlines()[1:]
                if (f := ln.split(",")) and len(f) >= 4 and f[1] in MATCHED)
        rows.append((day, o - prev, o))
        prev = o
    return [t for t in rows if t[1] != 0]


def render_timechart(series, total, keep=30):
    """Per-day rows showing cumulative progress + a cumulative sparkline. Each row's
    bar is the cumulative coverage as a fraction of the TOTAL function count — same
    fill style (█/░) and denominator as the OVERALL COVERAGE bar, so a row reads as
    "how full the board was at end of that day". Also carries the cumulative coverage
    %% and the day's growth in percentage points of the total. Reads
    top(oldest)->bottom(newest). Returns markdown lines (empty if no history)."""
    if not series:
        return []
    shown = series[-keep:]
    hidden = len(series) - keep
    cur = shown[-1][2]
    L = ["## Progress over time\n", "```",
         "  DAILY PROGRESS  —  byte-exact (O) functions matched (cumulative)"]
    if hidden > 0:
        L.append(f"  (showing the last {keep} active days; {hidden} earlier hidden)")
    L.append("")
    L.append(f"  cumulative  {sparkline([c for _, _, c in shown])}  "
             f"{cur:,} matched · {pct(cur, total):.2f}% of {total:,}")
    L.append("")
    L.append("  date   coverage (cumulative, % of total)          matched   cov%    +day   +cov%")
    for day, delta, cum in shown:
        L.append(f"  {day[5:]}  [{bar(cum / total, 30)}]  {cum:>6}  {pct(cum, total):>5.2f}%  "
                 f"{delta:>+5}  {pct(delta, total):>+5.2f}%")
    L.append("```")
    L.append("")
    return L


def render_heatmap(series):
    """GitHub-style contribution calendar from the same git-derived series: weeks are
    columns (oldest left), weekdays are rows (Sun top), each cell shaded by the number
    of functions matched that day (quartile buckets of the nonzero daily counts). Shows
    the project's span, padded to at least 13 weeks and capped at ~a year."""
    RAMP = " ·░▒▓█"   # [0]=future/blank, [1]=zero day, [2..5]=quartiles
    if not series:
        return []
    delta = {datetime.date.fromisoformat(d): n for d, n, _ in series}
    days = sorted(delta)
    first, last = days[0], days[-1]
    sun = lambda d: d - datetime.timedelta(days=(d.weekday() + 1) % 7)  # Sunday of d's week
    last_sun = sun(last)
    span_weeks = (last_sun - sun(first)).days // 7 + 1
    # show the project's whole span, but pad a young project up to a readable window
    # (like GitHub always showing a calendar) and cap at ~a year
    n_weeks = min(53, max(span_weeks, 13))
    first_sun = last_sun - datetime.timedelta(weeks=n_weeks - 1)
    weeks = [first_sun + datetime.timedelta(weeks=w) for w in range(n_weeks)]
    vals = sorted(v for v in delta.values() if v > 0)
    q = lambda p: vals[min(len(vals) - 1, int(p * (len(vals) - 1)))] if vals else 0
    q1, q2, q3 = q(0.25), q(0.50), q(0.75)

    def cell(day):
        if day > last:                    # a future day (beyond the newest data): blank
            return RAMP[0]
        v = delta.get(day, 0)             # any past day, incl. before the project began
        return RAMP[1] if v <= 0 else RAMP[2 + (v > q1) + (v > q2) + (v > q3)]

    month_line = [" "] * n_weeks
    prev_m, reserved_until = None, -1
    for i, wk in enumerate(weeks):
        if wk.month != prev_m:
            prev_m = wk.month
            if i > reserved_until:
                for k, ch in enumerate(wk.strftime("%b")):
                    if i + k < n_weeks:
                        month_line[i + k] = ch
                reserved_until = i + 2
    labels = {1: "Mon", 3: "Wed", 5: "Fri"}
    L = ["  contribution calendar — functions matched per day", "```",
         "     " + "".join(month_line)]
    for r in range(7):
        row = "".join(cell(wk + datetime.timedelta(days=r)) for wk in weeks)
        L.append(f" {labels.get(r, '   '):<3} {row}")
    L.append("")
    L.append(f"  Less {RAMP[1]}{RAMP[2]}{RAMP[3]}{RAMP[4]}{RAMP[5]} More"
             f"   (quartile shading; thresholds {q1}/{q2}/{q3} matches/day)")
    L.append("```")
    L.append("")
    return L


def render():
    d = collect_csv()
    subs, mapped = subsystem_breakdown(d["o_syms"])
    today = datetime.date.today().isoformat()
    decompiled = d["o_n"] + d["p_n"]
    L = []
    L.append("# LEGO City Undercover — Decompilation Progress\n")
    L.append(f"_Nintendo Switch Edition · EU v1.0.3 `main` NSO · clean-room matching "
             f"decompilation · auto-generated snapshot {today}_\n")
    L.append("```")
    L.append("╔══════════════════════════════════════════════════════════════════╗")
    L.append("║       LEGO CITY UNDERCOVER  —  DECOMP PROGRESS BOARD              ║")
    L.append("╚══════════════════════════════════════════════════════════════════╝")
    L.append("")
    L.append("  OVERALL FUNCTION COVERAGE")
    L.append(f"    {d['o_n']:>5} / {d['total_n']:>6} functions matched")
    L.append(f"    [{bar(d['o_n'] / d['total_n'])}] {pct(d['o_n'], d['total_n']):.2f}%")
    L.append(f"    by code size:  {d['o_b']:,} / {d['total_b']:,} bytes  "
             f"({pct(d['o_b'], d['total_b']):.2f}%)")
    L.append("")
    L.append(f"  MATCH QUALITY  (of {decompiled} functions decompiled so far)")
    L.append(f"    byte-exact (O)   {d['o_n']:>5}  [{bar(pct(d['o_n'], decompiled) / 100)}] "
             f"{pct(d['o_n'], decompiled):.0f}%")
    L.append(f"    in progress M/m  {d['p_n']:>5}  [{bar(pct(d['p_n'], decompiled) / 100)}] "
             f"{pct(d['p_n'], decompiled):.0f}%")
    L.append("")
    if subs:
        L.append(f"  MATCHED BY SUBSYSTEM  ({mapped} of {d['o_n']} localised)")
        for sub, n in subs.most_common():
            L.append(f"    {sub:<12}{n:>5}  [{bar(n / d['o_n'])}]")
    else:
        L.append("  MATCHED BY SUBSYSTEM")
        L.append("    (run tools/build.py first — subsystem map is read from build/)")
    L.append("```")
    L.append("")
    series = daily_series()
    L += render_timechart(series, d["total_n"])
    L += render_heatmap(series)
    L.append("## Phases / subsystems\n")
    active = subs or Counter()
    # (label, keys summed for the count, description). Infra is a fixed DONE row.
    rows = [
        ("infra",   None,                       "toolchain (Clang 3.9.1) · devcontainer · GitHub CI byte-gate"),
        ("numath",  ["numath"],                 "vector / matrix / angle / random math leaves"),
        ("nucore",  ["nucore", "support"],      "engine core — threads, files, strings, checksums, compression"),
        ("legoapi", ["legoapi", "legogame"],    "game API — options, score, timers, localisation, actions"),
        ("kestrel", ["kestrel"],                "kestrel scripting / action layer"),
        ("render",  ["nu2api", "nu3d", "chroma", "edlevel", "edtools"],
                                                "2D/3D API, rendering, level & tools"),
    ]
    L.append("```")
    for label, keys, desc in rows:
        if keys is None:
            frac, status = 1.0, "✅ DONE"
        else:
            n = sum(active.get(k, 0) for k in keys)
            frac = min(n / 300.0, 1.0)  # coarse visual scale over the per-subsystem leaf pool
            status = f"🟢 ACTIVE ({n})" if n else "⚪ PENDING"
        L.append(f" {label:<9} [{bar(frac, 20)}] {status}")
        L.append(f"     {desc}")
    L.append("```")
    L.append("")
    L.append("> Matching runs bottom-up: call-free leaf functions in the math and core "
             "libraries first (they have no dependencies and stable ABI), widening into the "
             "game API and scripting layers as their callees land. The board reflects the "
             "committed ledger, so it never drifts from `master`.\n")
    L.append("## What's matched\n")
    L.append("The Switch build was compiled with **Clang and ships symbols**, so functions "
             "carry their real (mangled) names and are organised into the original engine "
             "subsystems under `src/` (`numath`, `nucore`, `legoapi`, `kestrel`, …). Every "
             "function counted here is **byte-for-byte identical** to the retail EU v1.0.3 "
             "`main` NSO — verified objectively by `tools/check`, which diffs the compiled "
             "object against the original binary. There is no \"close enough\" tier: a "
             "function is `O` (matching) only when the bytes are exact. Functions that are "
             "decompiled but not yet bit-exact stay `M`/`m` (major/minor diffs) and are "
             "**never** merged as matching — CI rejects any `W` state (AGENTS.md §4).\n")
    L.append("## Pipeline\n")
    L.append("`tools/setup.py <main>` installs the pinned toolchain and stages the target "
             "(clean-room: you provide your own dump). `tools/build.py` compiles `src/` with "
             "the pinned Clang 3.9.1 flags; `tools/check` byte-compares each function against "
             "the original NSO; `tools/common/progress.py` reports coverage. This board is "
             "regenerated by `tools/wiki/gen_progress.py` as part of the merge cycle "
             "(AGENTS.md §4). The match ledger lives in `data/lcuswitch_functions.csv`.\n")
    L.append(f"---\n_Denominator: {d['total_n']:,} functions / {d['total_b']:,} bytes in the "
             "EU v1.0.3 `main` NSO. The NSO, the converted ELF, and all game assets are never "
             "committed (clean-room)._")
    return "\n".join(L)


def push(content):
    tok = os.environ["GITHUB_TOKEN"]
    host = os.environ.get("GITHUB_API_URL", "https://github.com")
    owner = os.environ.get("GITHUB_OWNER", "alfaiotadev")
    repo = os.environ.get("GITHUB_REPO", "Lego-City-Undercover-Decompilation")
    api = f"{host}/api/v1/repos/{owner}/{repo}/wiki"
    ctx = ssl.create_default_context()
    ctx.check_hostname = False
    ctx.verify_mode = ssl.CERT_NONE
    body = {"title": "Home", "content_base64": base64.b64encode(content.encode()).decode(),
            "message": "wiki: refresh decomp progress board"}
    hdr = {"Authorization": f"token {tok}", "Content-Type": "application/json"}
    # try update, fall back to create
    for method, url in (("PATCH", f"{api}/page/Home"), ("POST", f"{api}/new")):
        req = urllib.request.Request(url, data=json.dumps(body).encode(), method=method, headers=hdr)
        try:
            r = urllib.request.urlopen(req, context=ctx)
            print(f"wiki {method} {r.status}")
            return
        except urllib.error.HTTPError as e:
            if method == "POST":
                print(f"wiki push failed: {e.code} {e.read().decode()[:200]}")
                sys.exit(1)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-o", "--out", help="write markdown to this file")
    ap.add_argument("--push", action="store_true", help="update the wiki Home page via API")
    args = ap.parse_args()
    md = render()
    if args.out:
        open(args.out, "w").write(md)
        print(f"wrote {args.out}")
    if args.push:
        push(md)
    if not args.out and not args.push:
        print(md)


if __name__ == "__main__":
    main()
