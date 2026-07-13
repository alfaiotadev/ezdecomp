# CLAUDE.md

Claude Code-specific guide for the `Lego-City-Undercover-Decompilation` repo.

> **Read [`AGENTS.md`](./AGENTS.md) first.** It holds the full operational guide
> (rules, workflow, matching loop, directories) for all agents. This file does
> not repeat it — it only adds Claude Code-specific notes. Building/contributing
> context: [`docs/BUILDING.md`](./docs/BUILDING.md) and
> [`docs/CONTRIBUTING.md`](./docs/CONTRIBUTING.md).

---

## Checklist before starting work

1. You are in the Apple Silicon devcontainer (`linux/arm64`, native — no Rosetta,
   no qemu). Confirm the toolchain: `toolchain/bin/clang --version` (Clang 3.9.1).
2. The matching target is the **EU v1.0.3 `main` NSO** — the only binary. It is
   never in git; you provide your own dump via `tools/setup.py /path/to/main`.
3. Read AGENTS.md §2 (absolute rules) and §4 (workflow) before your first commit.

---

## Hard limits (AGENTS.md §2 condensed — these do not bend)

- **Do not add to git:** the NSO, the converted ELF, any game asset, or `.env`.
  The repo is clean-room: code, tools, docs only.
- **Never print, commit, or write the `GITHUB_TOKEN` value** anywhere. Only
  the `${GITHUB_TOKEN}` reference.
- **Do not merge without green CI.** Do not skip the verification gate. Never
  commit a `Quality=W` function to `data/lcuswitch_functions.csv`.
- **Do not bump Clang / libc++ / musl versions** as part of other work — that is
  its own PR.

If a task seems to require breaking one of the above, stop and ask the user
instead of working around the rule.

---

## Working style with Claude Code

- **One issue = one branch = one PR.** Follow the AGENTS.md §4 cycle. Name PRs
  `Implement <Name>` / `Work on <Name>` / `Complete <Name>` (CONTRIBUTING).
- **Code to files, not chat.** All reconstructed C++ goes into `src/` under the
  right subsystem directory (mirrors demangled symbols — see AGENTS.md §6).
  Pipeline scripts go in `tools/`. No copy-paste code blocks in chat.
- **Prove matching objectively.** After `python3 tools/build.py`, run
  `tools/check`. The diff is the source of truth — do not claim a match you have
  not verified with `check`.
- **When stuck**, don't force a partial merge. Leave the PR as a draft / non-
  matching (`Work on <Name>`) and move on, rather than committing a `W` state.
- **Escalate hard blockers to the advisor (default: spawn it yourself).** If a
  function won't match because of a pure compiler artifact (scheduling / register
  reuse / hoist-sink) or needs something outside the plain-C loop, spawn the
  **analysis-only advisor** with the `Agent` tool (`subagent_type: advisor`,
  defined in [`.claude/agents/advisor.md`](.claude/agents/advisor.md) — an
  empty-context, max-effort Opus with read-only tools, so it *cannot* implement).
  Give it the blocker, the target disasm, the exact source you tried, the
  verbatim `tools/check --always-diff` residual, and numbered questions; it
  returns a concrete fix + ruled-out dead ends. Implement proof-first, verify
  with `tools/check`, ship the PR. Re-spawn with fresh data if only partly
  solved. For a whole hard function/family, instead spawn a general-purpose Opus
  subagent that iterates the build/`check` loop itself and returns matching
  source. **Fallback** (subagent capacity rate-limited, or the heaviest
  problems): open a GitHub issue labelled **`fable`** with the self-contained
  residual and hand it to the claude.ai advisor (Fable, `claude-fable-5`) or a
  separate max-effort Opus session — see AGENTS.md §4 "Escalating blockers (the
  advisor)" and [`docs/FABLE_PROMPT.md`](docs/FABLE_PROMPT.md). Never commit a
  `W` state; leave the function at its honest state either way.

---

## Useful commands (in the container)

```bash
# One-time setup with the game binary (clean-room: your own dump)
tools/setup.py /path/to/main            # EU v1.0.3 main NSO
tools/setup.py --project-only           # toolchain + build dir, no binary

# Build + verify
python3 tools/build.py                  # build
tools/check                             # verify matches against the original
python3 tools/common/progress.py        # overall progress

# After a function-match merge lands on master: refresh the wiki board (§4 step 7)
python3 tools/wiki/gen_progress.py --push

# Share a scratch for a tricky function
tools/decompme <Function Name>

# GitHub API (token from .env, never as a literal)
set -a; source .env; set +a
curl -sS -H "Authorization: token ${GITHUB_TOKEN}" \
  "https://api.github.com/repos/alfaiotadev/ezdecomp/issues?state=open"
```

> The canonical compile flags live in `tools/config.toml` and the CMake
> toolchain (`toolchain/ToolchainNX64.cmake`). Use them, don't invent your own.
