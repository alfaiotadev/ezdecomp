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
import datetime, json, math, os, re, subprocess

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


MODEL_NAMES = {  # commit trailer slug -> display name
    "kimi-k2-7": "Kimi K2.7", "kimi-k2": "Kimi K2", "swe-1.7": "SWE-1.7",
    "glm-5.2": "GLM-5.2", "devstral2": "Devstral 2", "claude": "Claude",
}
BOT_AUTHORS = {"alfaiotadev", "alfaiotadev-bot"}
FALLBACK_MODEL = "Kimi K2.7"  # all pre-trailer autonomous landings were Kimi via the Devin CLI


GTA_VI = datetime.date(2026, 10, 19)  # the (totally serious) deadline


def eta(matched, total, cal, today):
    """Naive linear finish estimate at the recent match rate, vs the GTA VI date."""
    days = cal.get("days", [])
    remaining = total - matched
    if not days or remaining <= 0:
        return {"rate": 0, "remaining": remaining}
    dates = [datetime.date.fromisoformat(d) for d, _ in days]
    span = (max(dates) - min(dates)).days + 1
    rate = cal["total"] / span
    if rate <= 0:
        return {"rate": 0, "remaining": remaining}
    eta_days = math.ceil(remaining / rate)
    eta_date = today + datetime.timedelta(days=eta_days)
    return {"rate": round(rate, 1), "remaining": remaining, "eta_days": eta_days,
            "eta_date": eta_date.isoformat(), "eta_year": eta_date.year,
            "gta_date": GTA_VI.isoformat(), "days_vs_gta": (eta_date - GTA_VI).days}


def contributors():
    """Attribute each function landing (commit "Implement/Complete/Work on ...") to a
    contributor: an explicit `Matched-by: <slug>` commit trailer (autonomous model) wins;
    else a bot-authored landing = the autonomous model (Kimi); else the git author (human).
    Returns [{name, count, kind}] with kind 'model' or 'human', biggest first."""
    try:
        out = subprocess.run(
            ["git", "-C", REPO, "log", "--no-merges", "--format=%x1e%an%x1f%s%x1f%b"],
            capture_output=True, text=True).stdout
    except Exception:
        return []
    counts, kind = {}, {}
    for rec in out.split("\x1e"):
        if not rec.strip():
            continue
        parts = rec.split("\x1f")
        an = parts[0].strip()
        subj = parts[1] if len(parts) > 1 else ""
        body = parts[2] if len(parts) > 2 else ""
        if not subj.startswith(("Implement ", "Complete ", "Work on ")):
            continue
        m = re.search(r"(?im)^Matched-by:\s*(\S+)", body)
        if m:
            name = MODEL_NAMES.get(m.group(1).lower(), m.group(1)); k = "model"
        elif an in BOT_AUTHORS:
            name = FALLBACK_MODEL; k = "model"
        else:
            name = an; k = "human"
        counts[name] = counts.get(name, 0) + 1
        kind[name] = k
    return [{"name": n, "count": c, "kind": kind[n]}
            for n, c in sorted(counts.items(), key=lambda x: -x[1])[:8]]


def main():
    total_n, total_b, o_n, o_b, p_n, families = collect()
    cum = cumulative_by_day()
    stamp = os.environ.get("SOURCE_DATE_EPOCH")
    now = datetime.datetime.fromtimestamp(int(stamp), datetime.timezone.utc) if stamp else None
    generated = now.strftime("%Y-%m-%d %H:%M UTC") if now else ""
    today = now.date() if now else max((datetime.date.fromisoformat(d) for d, _ in cum), default=datetime.date(2026, 1, 1))
    cal = calendar(cum)
    data = {
        "generated": generated,
        "total_n": total_n, "total_b": total_b,
        "matched_n": o_n, "matched_b": o_b, "inprogress_n": p_n,
        "pct_fn": round(o_n / total_n * 100, 2) if total_n else 0,
        "pct_code": round(o_b / total_b * 100, 2) if total_b else 0,
        "series": [[d, c] for d, c in cum],
        "families": families,
        "calendar": cal,
        "eta": eta(o_n, total_n, cal, today),
        "contributors": contributors(),
    }
    out = os.path.join(REPO, "docs", "progress.json")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    json.dump(data, open(out, "w"), separators=(",", ":"))
    print("wrote %s (%d/%d matched, %.2f%%, %d families, map=%d syms)"
          % (out, o_n, total_n, data["pct_fn"], len(families), len(SUBMAP)))


if __name__ == "__main__":
    main()
