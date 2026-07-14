#!/usr/bin/env python3
"""
crowdship.py — land a locally byte-matched function onto the public ezdecomp repo.

The autonomous-agent lane of the crowdsource pipeline. Humans use decomp.me in a
browser; autonomous agents (e.g. Kimi via the Devin CLI) can't — decomp.me's
/compile API is Cloudflare-blocked — so they match locally with tools/check (which
needs the binary) and this bot lands the result publicly.

Runs in the devcontainer: /workspace has the binary + tools/check + the agent's
uncommitted change; /home/decomp/ezdecomp is a PAT-authed clone of the public repo.
Flow: re-verify tools/check == OK -> copy the changed src (+ CSV row) into ezdecomp
-> branch/commit/push -> open PR ("Closes #issue") -> squash-merge.

Usage: crowdship.py --symbol <mangled> [--issue N]
Env:   ALFAIOTADEV_GH_PAT (or GITHUB_TOKEN)
"""
import argparse, json, os, shutil, subprocess, sys, time, urllib.request, urllib.error

WS = "/workspace"
EZ = "/home/decomp/ezdecomp"
REPO = "alfaiotadev/ezdecomp"


def sh(cmd, cwd=None):
    return subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)


def gh(method, path, tok, body=None):
    req = urllib.request.Request(
        "https://api.github.com" + path,
        data=json.dumps(body).encode() if body else None, method=method,
        headers={"Authorization": "Bearer " + tok, "Accept": "application/vnd.github+json",
                 "Content-Type": "application/json", "User-Agent": "crowdship"})
    return json.load(urllib.request.urlopen(req))


def demangle(s):
    r = sh(["c++filt", s])
    return (r.stdout or s).strip()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--symbol", required=True)
    ap.add_argument("--issue", type=int)
    a = ap.parse_args()
    tok = os.environ.get("ALFAIOTADEV_GH_PAT") or os.environ.get("GITHUB_TOKEN")
    if not tok:
        sys.exit("no PAT (set ALFAIOTADEV_GH_PAT)")

    # 1. re-verify the byte match locally (authoritative gate)
    r = sh(["tools/check", a.symbol, "--no-pager"], cwd=WS)
    if "OK" not in (r.stdout + r.stderr):
        sys.exit("tools/check did NOT report OK for %s; refusing to land.\n%s"
                 % (a.symbol, (r.stdout + r.stderr)[-400:]))
    print("verified OK:", a.symbol)

    # 2. collect the agent's changed files (src + the CSV ledger)
    st = sh(["git", "-C", WS, "status", "--porcelain"]).stdout
    files = [ln[3:].strip() for ln in st.splitlines() if ln.strip()]
    files = [f for f in files if f.startswith("src/") or f == "data/lcuswitch_functions.csv"]
    if not files:
        sys.exit("no changed src/CSV files in /workspace to land")
    print("landing files:", files)

    # 3. branch off ezdecomp/main, copy the files in, commit, push
    dm = demangle(a.symbol)
    branch = "bot/" + "".join(c if c.isalnum() else "-" for c in a.symbol)[:50]
    for c in (["git", "-C", EZ, "fetch", "-q", "origin"],
              ["git", "-C", EZ, "checkout", "-q", "-B", branch, "origin/main"]):
        if sh(c).returncode:
            sys.exit("git failed: " + " ".join(c))
    for f in files:
        dst = os.path.join(EZ, f)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copy2(os.path.join(WS, f), dst)
        sh(["git", "-C", EZ, "add", f])
    if sh(["git", "-C", EZ, "diff", "--cached", "--quiet"]).returncode == 0:
        sys.exit("no net change vs ezdecomp/main (already landed?)")
    model = os.environ.get("CROWD_MODEL", "kimi-k2-7")
    msg = "Implement " + dm
    sh(["git", "-C", EZ, "commit", "-q", "-m", msg + "\n\nMatched-by: " + model])
    if sh(["git", "-C", EZ, "push", "-q", "-f", "origin", branch]).returncode:
        sys.exit("push failed")
    print("pushed", branch)

    # 4. open a PR ("Closes #issue") and squash-merge
    body = "Autonomous-agent contribution — byte-verified locally with `tools/check` (OK).\n"
    if a.issue:
        body += "\nCloses #%d\n" % a.issue
    pr = gh("POST", "/repos/%s/pulls" % REPO, tok,
            {"title": msg, "head": branch, "base": "main", "body": body})
    num = pr["number"]
    print("opened PR #%d: %s" % (num, pr["html_url"]))
    for _ in range(10):
        info = gh("GET", "/repos/%s/pulls/%d" % (REPO, num), tok)
        if info.get("mergeable") is not None:
            break
        time.sleep(2)
    try:
        gh("PUT", "/repos/%s/pulls/%d/merge" % (REPO, num), tok,
           {"merge_method": "squash", "commit_title": "%s (#%d)" % (msg, num),
            "commit_message": "Matched-by: " + model})
        print("MERGED PR #%d%s" % (num, (" (closes #%d)" % a.issue) if a.issue else ""))
    except urllib.error.HTTPError as e:
        print("merge deferred: %d %s (PR left open for review)" % (e.code, e.read().decode()[:150]))


if __name__ == "__main__":
    main()
