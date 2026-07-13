# Workflow reference: tooling, CSV, escalation, and shipping

## `dc.py` — the helper (at `tools/dc.py`)
```bash
python3 tools/dc.py disasm <mangled_symbol> [<sym> …]
#   → masked-address objdump of the target from data/main.elf
#     (looks up addr+size in the CSV; prints a header + instructions)

python3 tools/dc.py setstate <mangled_symbol> <O|m|M|U>
#   → rewrites the Quality column for that symbol in the CSV. (No W — by design.)

python3 tools/dc.py status <PR#>
#   → prints the combined CI status for a PR's head commit.

python3 tools/dc.py ship --branch B --title T --body BODY \
        --issue-title IT --issue-body IB [--no-wiki]
#   → full push→issue→PR→wait-CI→squash-merge→ff-master→rebuild→wiki. See SHIP.
```
`ship` and `status` need the token in the environment first:
`set -a; source .env; set +a`.

## Build & check
```bash
python3 tools/build.py            # build (add --clean if the source set changed)
tools/check <symbol>              # byte-diff one function vs the original NSO
tools/check --always-diff <symbol># show the asm diff even when it matches
tools/check                       # no arg → check the WHOLE tree
python3 tools/common/progress.py  # overall coverage
python3 tools/lint.py --format    # clang-format + checks (run before a PR)
```
`check` is the source of truth: it ends in `OK` for a byte-exact match, otherwise
prints a target-vs-yours asm diff. Do not claim a match you haven't seen `check`
confirm. **Never run two builds in `/workspace` at once.**

## `data/lcuswitch_functions.csv`
Columns: `Address,Quality,Size,Name` (mangled symbol; may be empty for stubs).
Address is a full VA (`0x0000007100…`); the low 32 bits are the ELF offset.

Quality codes:
| Code | Meaning | Notes |
|---|---|---|
| `O` | Matching — **byte-exact** | the only "done" state |
| `m` | Equivalent — functionally identical, minor codegen diff | legitimate end state for irreducible artifacts |
| `M` | NonMatching — decompiled, major diffs | still work to do |
| `U` | NotDecompiled — untouched | the default |
| `W` | Wip | **CI REJECTS THIS — never commit it** |
| `L` | Library function | should not be decompiled |

Before finishing, confirm no stray `W`:
`awk -F, 'NR>1 && $2=="W"' data/lcuswitch_functions.csv` must print nothing.

## Compile flags — do NOT hardcode or invent
Canonical source of truth: **`tools/config.toml`** and
**`toolchain/ToolchainNX64.cmake`**. `tools/build.py` uses them. The build is
**`-O3 -std=c++1z -fno-exceptions -fno-strict-aliasing`**, target
`aarch64-linux-elf`, `-mcpu=cortex-a57+fp+simd+crypto+crc -mno-implicit-float
-stdlib=libc++ -fPIC`. (Note: the `advisor` agent prompt mentions `-O2` — that is
stale; the real build is `-O3` per `config.toml`. Don't copy `-O2` anywhere.)

---

## Escalating a blocker
When you can't tell if a residual is fixable, hand it off with the *full* context
— never a vague "it doesn't match."

**In Claude Code — spawn the `advisor` subagent** (`subagent_type: advisor`;
analysis-only, read-only, max-effort). Give it:
1. the target disassembly (`dc.py disasm <sym>`),
2. the exact source you tried (paste it),
3. the **verbatim `tools/check --always-diff <sym>` residual**,
4. numbered questions,
5. the dead ends you already ruled out.
It returns a one-line verdict — `bit-exact` (with source), `functional` (accept
`m`), `tooling-fix`, or `genuine-limit` — plus the concrete fix and ruled-out
paths. Implement proof-first, re-check, then proceed.

**On a harness without the advisor subagent** — open a GitHub issue labelled
**`fable`** containing the same self-contained residual, and hand it to the
claude.ai advisor (Fable). Template: `docs/FABLE_PROMPT.md`.

Either way: **never commit `W`**; leave the function at its honest state.

---

## SHIP — full autonomous lifecycle (OPT-IN ONLY)

Only run this when the user explicitly asked you to ship/merge (or passed
`--ship`). The default flow **stops at a verified match and hands off**. Shipping
merges to `master`, so a weaker model should not do it unprompted.

Preconditions: the function is `O` (or an honest, advisor-confirmed `m`); tree is
clean; `tools/lint.py --format` run; no `W` anywhere in the CSV.

**Step 0 — start from a clean, current master (do this BEFORE you pick a
function).** Otherwise your branch is based on a stale master and your PR drags
in already-merged work. `set -a; source .env; set +a` FIRST — the devcontainer's
*ambient* `GITHUB_TOKEN` is frozen at container creation and goes stale
after a token rotation, so sourcing the file (which overrides the ambient) is
what makes auth work:
```bash
set -a; source .env; set +a          # override the stale ambient token; never print it
git checkout master
git reset --hard HEAD                 # drop any leftover changes from a prior run
GIT_SSL_NO_VERIFY=1 git -c credential.helper= pull \
  "https://alfaiotadev:${GITHUB_TOKEN}@github.com/alfaiotadev/ezdecomp.git" master
```
(`credential.helper=` bypasses the container's VS Code credential helper; the
`origin` remote is a broken ssh URL, so always push/pull via the explicit HTTPS
token URL.)

```bash
set -a; source .env; set +a          # load ${GITHUB_TOKEN} (never print it)
git checkout -b feat/<desc>          # from the synced master; one issue = one branch = one PR
git add src/<your-file(s)> data/lcuswitch_functions.csv   # stage only YOUR function (not -A)
git commit -m "Implement <Name>"                          # small logical commits

python3 tools/dc.py ship \
  --branch feat/<desc> \
  --title  "Implement <Name>" \
  --body   "<what matched + residual notes>" \
  --issue-title "Implement <Name>" \
  --issue-body  "<acceptance criterion, e.g. '<Name> matches'>"
```
`ship` pushes the branch, opens the issue + PR (`Closes #n`), polls CI every 15s,
and **only squash-merges if CI is green** (else it prints "NOT merging" and
exits). On success it deletes the branch, fast-forwards `master`, rebuilds, and
refreshes the wiki progress board (pass `--no-wiki` to skip).

PR title convention: `Implement <Name>` (matching), `Work on <Name>` (partial),
`Complete <Name>`.

### git-over-HTTPS & the stale-ref gotcha (container has no working ssh)
- Push/merge is over HTTPS with the token; `dc.py` injects it at runtime. **Never
  print, commit, or write the token value — only `${GITHUB_TOKEN}`.**
- **Do NOT `git reset --hard origin/master`** — that ref is stale and discards
  merged work. After a `ship`, sync to the SHA `ship` reported:
  ```bash
  git reset --hard <ship-reported-SHA>
  git update-ref refs/remotes/origin/master <SHA>
  ```
  Recover any lost commits with `git reflog`.
- Manual force-push if ever needed:
  ```bash
  GIT_SSL_NO_VERIFY=1 git push -f \
    "https://alfaiotadev:${GITHUB_TOKEN}@github.com/alfaiotadev/ezdecomp.git" <branch>
  ```
- Refresh the wiki after a merge if you skipped `--no-wiki`:
  `python3 tools/wiki/gen_progress.py --push`.
