#!/usr/bin/env bash
# crowd-autoloop.sh — autonomous crowdsource loop for the ezdecomp board.
#
# For each open `open`-label issue: run a fresh Kimi (`devin --print`) to match that
# function LOCALLY (tools/check == OK), then crowdship.py lands it on the public repo
# (PR + squash-merge, auto-closing the issue). Resets the /workspace tree between
# issues so each match is isolated. Fresh devin process per issue = fresh context.
#
# MUST run inside the arm64 devcontainer (needs Clang 3.9.1, dc.py, the binary, and a
# logged-in devin CLI). Humans use decomp.me in a browser; this is the AGENT lane.
#
# Env: CROWD_MODEL (default kimi-k2-7) · CROWD_MAX (default 40) ·
#      CROWD_ITER_TIMEOUT (default 30m) · CROWD_LOG_DIR (default ~/crowd-loop-logs)
set -uo pipefail

REPO="alfaiotadev/ezdecomp"
WS=/workspace
DEVIN="$HOME/.local/bin/devin"; command -v "$DEVIN" >/dev/null 2>&1 || DEVIN=devin
MODEL="${CROWD_MODEL:-kimi-k2-7}"
MAX="${CROWD_MAX:-40}"
ITER_TIMEOUT="${CROWD_ITER_TIMEOUT:-30m}"
LOGDIR="${CROWD_LOG_DIR:-$HOME/crowd-loop-logs}"; mkdir -p "$LOGDIR"
ATTEMPTED="$LOGDIR/attempted.txt"; : > "$ATTEMPTED"
export LIBCLANG_PATH="${LIBCLANG_PATH:-/usr/lib/aarch64-linux-gnu}"

set -a; . "$WS/.env" 2>/dev/null; set +a
TOK="${ALFAIOTADEV_GH_PAT:-${GITHUB_TOKEN:-}}"
[ -z "$TOK" ] && { echo "ERROR: no PAT (ALFAIOTADEV_GH_PAT)"; exit 1; }
export ALFAIOTADEV_GH_PAT="$TOK"

if "$DEVIN" auth status 2>&1 | grep -qi "not logged in"; then
  echo "ERROR: devin not logged in ($DEVIN auth login)"; exit 1
fi

cd "$WS"
if [ -n "$(git status --porcelain)" ]; then
  echo "ABORT: /workspace has uncommitted changes — refusing to run (would reset your work):"
  git status --porcelain | head; exit 1
fi

# print "NUMBER SYMBOL" of the oldest open `open`-label issue not in $ATTEMPTED
# whose function is still matchable (CSV quality U or M — skip irreducible `m` and done `O`)
fetch_issue() {
  ATTEMPTED="$ATTEMPTED" python3 - "$TOK" <<'PY'
import json,os,re,sys,urllib.request
tok=sys.argv[1]
done=set()
try:
    done={l.strip() for l in open(os.environ["ATTEMPTED"]) if l.strip()}
except FileNotFoundError: pass
# CSV quality + size per symbol (skip m = irreducible/done, O = matched)
qual={}; size={}
for ln in open("/workspace/data/lcuswitch_functions.csv"):
    p=ln.rstrip("\n").split(",")
    if len(p)>=4:
        qual[p[3]]=p[1]
        try: size[p[3]]=int(p[2])
        except ValueError: size[p[3]]=0
d=json.load(urllib.request.urlopen(urllib.request.Request(
 "https://api.github.com/repos/alfaiotadev/ezdecomp/issues?state=open&labels=open&per_page=100",
 headers={"Authorization":"Bearer "+tok,"User-Agent":"crowd","Accept":"application/vnd.github+json"})))
cands=[]
for it in d:
    if "pull_request" in it: continue
    if str(it["number"]) in done: continue
    m=re.search(r"\*\*Symbol:\*\*\s*`(_Z[\w.]+)`", it.get("body") or "")
    if not m: continue
    sym=m.group(1)
    if qual.get(sym) not in ("U","M"):   # skip irreducible m / already-O / unknown
        continue
    cands.append((size.get(sym,1<<30), it["number"], sym))
if cands:
    cands.sort()                          # smallest function first = easy-first throughput
    _,num,sym=cands[0]
    print(num, sym)
PY
}

echo "=== crowd-autoloop | model=$MODEL | cap=$MAX | timeout=$ITER_TIMEOUT ==="
n=0
while [ "$n" -lt "$MAX" ]; do
  read -r ISSUE SYM < <(fetch_issue) || true
  if [ -z "${SYM:-}" ]; then echo "no more open issues with a symbol — done."; break; fi
  n=$((n+1))
  echo "$ISSUE" >> "$ATTEMPTED"
  ts=$(date +%Y%m%d-%H%M%S); log="$LOGDIR/issue-$ISSUE-$ts.log"
  echo "-- [$n/$MAX] issue #$ISSUE  $SYM  -> $log"
  sed "s/__SYM__/$SYM/g" /home/decomp/crowd-loop.template > /home/decomp/crowd-cur.prompt
  timeout --signal=TERM --kill-after=30s "$ITER_TIMEOUT" "$DEVIN" \
     --prompt-file /home/decomp/crowd-cur.prompt --model "$MODEL" \
     --permission-mode dangerous --print > "$log" 2>&1 || echo "   (devin rc=$?)"
  if tools/check "$SYM" --no-pager 2>&1 | grep -q "^OK$\|OK"; then
    if python3 /home/decomp/crowdship.py --symbol "$SYM" --issue "$ISSUE" >> "$log" 2>&1; then
      echo "   LANDED #$ISSUE"
    else
      echo "   crowdship failed (see log)"
    fi
  else
    echo "   not matched — leaving issue open, moving on"
  fi
  # reset tree for the next issue: revert tracked edits AND remove any NEW untracked
  # src files the agent created (they've been landed on ezdecomp already).
  git checkout -- . 2>/dev/null || true
  git clean -fdq -- src/ 2>/dev/null || true
done
echo "=== crowd-autoloop done: attempted $n issue(s) ==="
