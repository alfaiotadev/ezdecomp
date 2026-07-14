#!/usr/bin/env python3
"""
gen_progress_json.py — emit a compact progress summary for the GitHub Pages dashboard.

Pure function of committed repo state (data/lcuswitch_functions.csv + its git history) —
no build, no binary. Writes docs/progress.json:
  generated, total_n/total_b, matched_n/matched_b, inprogress_n, pct_fn, pct_code,
  series [[date, cumulative_matched]...],
  families [{key,label,color,matched,total}...]  (matched-O split by subsystem/family),
  calendar {days:[[date,count]...], total, streak, max}  (functions matched per day),
  contributors [{name, count}...]  (git commit authors)
"""
import datetime, json, os, re, subprocess

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV = os.path.join(REPO, "data", "lcuswitch_functions.csv")
CSV_REL = "data/lcuswitch_functions.csv"
MATCHED = {"O"}
INPROGRESS = {"M", "m"}

# (key, label, color, ordered regexes tried against the leading identifier)
FAMILIES = [
    ("numath",  "Math",      "#58a6ff", r"^Nu(Vec|Mtx|Quat|Ang|Pln|Math|Misc|Equiv|Pow|Lerp|Rand|Interp|Clamp|Sqrt|Trig|Fix)"),
    ("render",  "Render/3D", "#f0883e", r"^Nu(Render|Display|Pvs|Tex|Portal|Occlusion|Mtl|Viewport|Video|Movie|Anim|Draw|Scene|Light|Cam|Mesh|Model|Gfx|2d|3d)"),
    ("nucore",  "Core",      "#a371f7", r"^Nu(File|Str|String|Thread|CheckSum|Serialize|Locale|Fpar|Sys|Time|Load|Input|Pad|Mem|Table|Heap|Sound|Audio)"),
    ("kestrel", "Scripting", "#3fb950", r"^(SAction|CharacterAction|VehicleAction|.*Action$|SVar|Script|Flow)"),
    ("legoapi", "Game API",  "#db61a2", r"^(Api|Options|Score|Lego|Mech|City|Player|Vehicle|Character|Mission|Objective|HUD|UI)"),
]
OTHER = ("other", "Other", "#8b949e")


def leading_ident(mangled):
    # _ZN<len><name>...  (member: class) OR  _Z<len><name>...  (free function)
    m = re.match(r"^_ZN?(\d+)(.+)$", mangled)
    if not m:
        return mangled
    n = int(m.group(1))
    return m.group(2)[:n]


def classify(mangled):
    ident = leading_ident(mangled)
    for key, _, _, rx in FAMILIES:
        if re.search(rx, ident):
            return key
    return OTHER[0]


def collect():
    total_n = total_b = o_n = o_b = p_n = 0
    fam = {k: [0, 0] for k, *_ in FAMILIES}
    fam[OTHER[0]] = [0, 0]
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
            if not name:
                continue
            k = classify(name)
            fam[k][1] += 1
            if q in MATCHED:
                o_n += 1
                o_b += b
                fam[k][0] += 1
            elif q in INPROGRESS:
                p_n += 1
    families = []
    for key, label, color, _ in FAMILIES + [(OTHER[0], OTHER[1], OTHER[2], None)]:
        matched, tot = fam[key]
        if matched or tot:
            families.append({"key": key, "label": label, "color": color,
                             "matched": matched, "total": tot})
    families.sort(key=lambda x: -x["matched"])
    return total_n, total_b, o_n, o_b, p_n, families


def cumulative_by_day():
    """[(iso_date, cumulative_O)] for days the O-count changed, from the CSV git history."""
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
    """Per-day NEW matches (deltas), excluding the initial import (baseline = first
    commit's O count). Returns {days, total, streak, max}."""
    if len(cum) < 2:
        return {"days": [], "total": 0, "streak": 0, "max": 0}
    days = []
    for i in range(1, len(cum)):
        d = cum[i][1] - cum[i - 1][1]
        if d > 0:
            days.append([cum[i][0], d])
    total = sum(d for _, d in days)
    mx = max((d for _, d in days), default=0)
    # streak: consecutive calendar days up to the latest active day
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
    top = sorted(counts.items(), key=lambda x: -x[1])[:8]
    return [{"name": n, "count": c} for n, c in top]


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
    print("wrote %s (%d/%d matched, %.2f%%, %d families, %d contributors)"
          % (out, o_n, total_n, data["pct_fn"], len(families), len(data["contributors"])))


if __name__ == "__main__":
    main()
