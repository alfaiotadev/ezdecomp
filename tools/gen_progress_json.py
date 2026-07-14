#!/usr/bin/env python3
"""
gen_progress_json.py — emit a compact progress summary for the GitHub Pages dashboard.

Pure function of committed repo state (data/lcuswitch_functions.csv + its git history
+ data/symbol_subsystems.json) — no build, no binary. Writes docs/progress.json:
  generated, total_n/total_b, matched_n/matched_b, inprogress_n, pct_fn, pct_code,
  series [[date, cumulative_matched]...],
  families [{key,label,color,matched}...]  (matched-O split by real src subsystem),
  calendar {days:[[date,count]...], total, streak, max}, contributors [{name,count}...]

data/symbol_subsystems.json (symbol -> src subsystem dir) is generated in the
devcontainer with `nm` over build objects (accurate); regenerate occasionally.
"""
import datetime, json, os, subprocess

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV = os.path.join(REPO, "data", "lcuswitch_functions.csv")
CSV_REL = "data/lcuswitch_functions.csv"
MATCHED = {"O"}
INPROGRESS = {"M", "m"}

# real src subsystem dir -> (family key, label, color)
SUB2FAM = {
    "kestrel": ("kestrel", "Scripting", "#3fb950"),
    "numath":  ("numath",  "Math",      "#58a6ff"),
    "nucore":  ("nucore",  "Core",      "#a371f7"),
    "legoapi": ("game",    "Game API",  "#db61a2"), "legogame": ("game", "Game API", "#db61a2"),
    "nu2api":  ("render",  "Render/3D", "#f0883e"), "nu3d": ("render", "Render/3D", "#f0883e"),
    "chroma":  ("render",  "Render/3D", "#f0883e"),
    "support": ("tools",   "Support/Tools", "#e3b341"), "edlevel": ("tools", "Support/Tools", "#e3b341"),
    "edtools": ("tools",   "Support/Tools", "#e3b341"), "(root)":  ("tools", "Support/Tools", "#e3b341"),
}
FAM_ORDER = [("kestrel", "Scripting", "#3fb950"), ("numath", "Math", "#58a6ff"),
             ("nucore", "Core", "#a371f7"), ("game", "Game API", "#db61a2"),
             ("render", "Render/3D", "#f0883e"), ("tools", "Support/Tools", "#e3b341"),
             ("other", "Other", "#8b949e")]

SUBMAP = {}
try:
    SUBMAP = json.load(open(os.path.join(REPO, "data", "symbol_subsystems.json")))
except Exception:
    pass


def fam_of(symbol):
    sub = SUBMAP.get(symbol)
    return SUB2FAM[sub][0] if sub in SUB2FAM else "other"


def collect():
    total_n = total_b = o_n = o_b = p_n = 0
    matched_by_fam = {}
    with open(CSV) as f:
        next(f)
        for line in f:
            p = line.rstrip("\n").split(",")
            if len(p) < 4:
                continue
            q, size, name = p[1], p[2], p[3]
            try:
                b = int(size)
            except ValueError:
                b = 0
            total_n += 1
            total_b += b
            if q in MATCHED:
                o_n += 1
                o_b += b
                if name:
                    k = fam_of(name)
                    matched_by_fam[k] = matched_by_fam.get(k, 0) + 1
            elif q in INPROGRESS:
                p_n += 1
    families = [{"key": k, "label": lab, "color": col, "matched": matched_by_fam[k]}
                for k, lab, col in FAM_ORDER if matched_by_fam.get(k)]
    return total_n, total_b, o_n, o_b, p_n, families


def cumulative_by_day():
    try:
        log = subprocess.run(["git", "-C", REPO, "log", "--format=%cs %H", "--", CSV_REL],
                             capture_output=True, text=True).stdout
    except Exception:
        return []
    last = {}
    for ln in log.splitlines():
        parts = ln.split(" ", 1)
        if len(parts) == 2:
            last.setdefault(parts[0], parts[1])
    rows, prev = [], None
    for day in sorted(last):
        blob = subprocess.run(["git", "-C", REPO, "show", "%s:%s" % (last[day], CSV_REL)],
                              capture_output=True, text=True).stdout
        o = sum(1 for l in blob.splitlines()[1:]
                if (f := l.split(",")) and len(f) >= 4 and f[1] in MATCHED)
        if o != prev:
            rows.append((day, o))
            prev = o
    return rows


def calendar(cum):
    if len(cum) < 2:
        return {"days": [], "total": 0, "streak": 0, "max": 0}
    days = [[cum[i][0], cum[i][1] - cum[i - 1][1]] for i in range(1, len(cum))
            if cum[i][1] - cum[i - 1][1] > 0]
    total = sum(d for _, d in days)
    mx = max((d for _, d in days), default=0)
    streak = 0
    if days:
        have = {datetime.date.fromisoformat(d) for d, _ in days}
        cur = max(have)
        while cur in have:
            streak += 1
            cur -= datetime.timedelta(days=1)
    return {"days": days, "total": total, "streak": streak, "max": mx}


def contributors():
    try:
        out = subprocess.run(["git", "-C", REPO, "log", "--no-merges", "--format=%an"],
                             capture_output=True, text=True).stdout
    except Exception:
        return []
    counts = {}
    for name in out.splitlines():
        name = name.strip()
        if name:
            counts[name] = counts.get(name, 0) + 1
    return [{"name": n, "count": c} for n, c in sorted(counts.items(), key=lambda x: -x[1])[:8]]


def main():
    total_n, total_b, o_n, o_b, p_n, families = collect()
    cum = cumulative_by_day()
    stamp = os.environ.get("SOURCE_DATE_EPOCH")
    generated = (datetime.datetime.fromtimestamp(int(stamp), datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")
                 if stamp else "")
    data = {
        "generated": generated,
        "total_n": total_n, "total_b": total_b,
        "matched_n": o_n, "matched_b": o_b, "inprogress_n": p_n,
        "pct_fn": round(o_n / total_n * 100, 2) if total_n else 0,
        "pct_code": round(o_b / total_b * 100, 2) if total_b else 0,
        "series": [[d, c] for d, c in cum],
        "families": families,
        "calendar": calendar(cum),
        "contributors": contributors(),
    }
    out = os.path.join(REPO, "docs", "progress.json")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    json.dump(data, open(out, "w"), separators=(",", ":"))
    print("wrote %s (%d/%d matched, %.2f%%, %d families, map=%d syms)"
          % (out, o_n, total_n, data["pct_fn"], len(families), len(SUBMAP)))


if __name__ == "__main__":
    main()
