#!/usr/bin/env python3
"""
gen_progress_json.py — emit a compact progress summary for the GitHub Pages dashboard.

Pure function of committed repo state (data/lcuswitch_functions.csv + its git history),
so it needs no build and no binary. Writes docs/progress.json:
  { generated, total_n, total_b, matched_n, matched_b, inprogress_n,
    pct_fn, pct_code, series: [[iso_date, cumulative_matched], ...] }
"""
import datetime, json, os, subprocess, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV = os.path.join(REPO, "data", "lcuswitch_functions.csv")
CSV_REL = "data/lcuswitch_functions.csv"
MATCHED = {"O"}
INPROGRESS = {"M", "m"}


def collect():
    total_n = total_b = o_n = o_b = p_n = 0
    with open(CSV) as f:
        next(f)
        for line in f:
            p = line.rstrip("\n").split(",")
            if len(p) < 4:
                continue
            q, size = p[1], p[2]
            try:
                b = int(size)
            except ValueError:
                b = 0
            total_n += 1
            total_b += b
            if q in MATCHED:
                o_n += 1
                o_b += b
            elif q in INPROGRESS:
                p_n += 1
    return total_n, total_b, o_n, o_b, p_n


def daily_series():
    """Cumulative byte-exact (O) count per activity-day, from the CSV's git history
    (last commit of each day). [(iso_date, cumulative), ...] for days that changed."""
    try:
        log = subprocess.run(["git", "-C", REPO, "log", "--format=%cs %H", "--", CSV_REL],
                             capture_output=True, text=True).stdout
    except Exception:
        return []
    last = {}
    for ln in log.splitlines():
        parts = ln.split(" ", 1)
        if len(parts) == 2:
            last.setdefault(parts[0], parts[1])  # first seen (newest) = last commit that day
    rows, prev = [], None
    for day in sorted(last):
        blob = subprocess.run(["git", "-C", REPO, "show", "%s:%s" % (last[day], CSV_REL)],
                              capture_output=True, text=True).stdout
        o = sum(1 for l in blob.splitlines()[1:]
                if (f := l.split(",")) and len(f) >= 4 and f[1] in MATCHED)
        if o != prev:
            rows.append([day, o])
            prev = o
    return rows


def main():
    total_n, total_b, o_n, o_b, p_n = collect()
    stamp = os.environ.get("SOURCE_DATE_EPOCH")
    generated = (datetime.datetime.fromtimestamp(int(stamp), datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")
                 if stamp else "")
    data = {
        "generated": generated,
        "total_n": total_n, "total_b": total_b,
        "matched_n": o_n, "matched_b": o_b, "inprogress_n": p_n,
        "pct_fn": round(o_n / total_n * 100, 2) if total_n else 0,
        "pct_code": round(o_b / total_b * 100, 2) if total_b else 0,
        "series": daily_series(),
    }
    out = os.path.join(REPO, "docs", "progress.json")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    json.dump(data, open(out, "w"), separators=(",", ":"))
    print("wrote %s (%d/%d matched, %.2f%%)" % (out, o_n, total_n, data["pct_fn"]))


if __name__ == "__main__":
    main()
