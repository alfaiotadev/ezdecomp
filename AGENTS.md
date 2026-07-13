# AGENTS.md

Operational guide for all agents (tool-agnostic) working in the
`Lego-City-Undercover-Decompilation` repo. Tool-specific guides reference this
file: `CLAUDE.md` (Claude Code) extends it, it does not repeat it.

> **Full building/contributing context:** [`docs/BUILDING.md`](docs/BUILDING.md)
> and [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md). Read them before making
> setup or workflow decisions. This file is the concise operational summary.

---

## 1 · What this project is

A **matching-level decompilation** of *Lego City Undercover* (**Nintendo Switch
Edition**) in C++. The Switch build was compiled with Clang and ships symbols,
which makes matching feasible — the Wii U build (GHS compiler, no symbols) is
not a viable target.

The goal is source that reassembles byte-for-byte to the original executable,
function by function, verified by an objective diff — not emulation.

**Matching target:** the original **EU v1.0.3 `main` NSO**.
- Compressed NSO sha256: `cf65ba2016505d83b9a0622704521651566b87510e60ebe0d4413546f2ea59c1`
- Uncompressed NSO sha256: `e9cdda9d68e30ce797c6cdf32a71ef8fe1eab269e4280a21cd5acd27611d70c8`
- US v1.0.2 likely works but is untested (different hash). JP is unsupported
  (different/unknown compiler). Do not match against other versions.

---

## 2 · Absolute rules (never break)

1. **No game data in version control.** The original NSO, the converted ELF, and
   anything derived from the game binary stay out of git (see `.gitignore`:
   `*.nso`, `*.elf`, `main`, `build/`). The repo contains **only code, tools,
   and documentation** (clean-room). If you are about to add a binary or asset
   to git — stop.
2. **No secrets in version control.** `.env` (the GitHub API token) is
   gitignored. `GITHUB_TOKEN` never lands in a commit, issue, PR
   description, commit message, log, code, or documentation. Use it only as an
   environment variable (`${GITHUB_TOKEN}`). If you notice it leaked,
   report and stop — it must be revoked.
3. **No incomplete merges.** Nothing merges to the default branch without green
   CI (build + function verification). CI is the quality gate, not a formality.
4. **Do not change toolchain versions lightly.** Clang 3.9.1, the libc++ 3.9.1
   headers, and the musl sysroot are pinned. A version bump can break already
   matched functions. A version change is its own deliberate PR, not a side
   effect.
5. **One version, one target.** All matching is done against the EU v1.0.3 `main`
   NSO. Do not compare against other versions.

---

## 3 · Development environment

- **Machine:** Apple Silicon Mac (arm64).
- **Editor:** VS Code + Dev Containers extension.
- **Container:** `linux/arm64` devcontainer that runs **natively — no Rosetta 2,
  no qemu emulation**. On Apple Silicon, [OrbStack](https://orbstack.dev) is the
  recommended Docker provider (native arm64; Docker Desktop also works). This is
  possible because the LCUDecompToolsCache release
  ships a native `aarch64-Linux` build of Clang 3.9.1; `tools/setup.py` selects
  it automatically via `{platform.machine()}-{platform.system()}` →
  `aarch64-Linux`. The matching target is `aarch64-linux-elf` regardless of host
  arch, so host architecture does not affect matching.
- Running LCU directly on the macOS host (outside the container) is also
  supported — the cache ships an `arm64-Darwin` build too.

Start: open the repo in VS Code → **Dev Containers: Reopen in Container**. The
first build installs OS deps; `postCreate` runs `tools/setup.py --project-only`
to download the pinned toolchain and create `build/`.

Verify the environment in the container:
```bash
toolchain/bin/clang --version   # Clang 3.9.1
tools/check --help || true
```

To add the game binary (clean-room: you provide your own legal dump):
```bash
tools/setup.py /path/to/main    # EU v1.0.3 main NSO
```

---

## 4 · Workflow: each task as its own issue → PR → merge

Every function match / feature / bugfix goes through the same cycle.

1. **Issue.** Short title; body states the acceptance criterion (e.g.
   "`cNuStringNode` matches" or "`sub_...` matches ≥ 99%"). Add labels /
   milestone if in use.
2. **Branch** from the default branch: `feat/<desc>`, `fix/<desc>`, or
   `tooling/<desc>`.
3. **Commits** in small logical steps, referencing the issue where relevant.
4. **PR** to the default branch. Use the naming convention from
   [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md):
   - Matching impl of a class/method: `Implement <Name>`
   - Non-matching / incomplete: `Work on <Name>`
   - Completion: `Complete <Name>`
5. **CI gate:** build + function verification + lint. Red → fix and push again.
   Do not merge before green.
6. **Merge** (squash). PRs are squashed and merged.
7. **Refresh the progress board.** After a function-match merge lands on
   `master`, the matched-function count changes: on up-to-date `master` with a
   build present, run `tools/build.py` then
   `tools/wiki/gen_progress.py --push` to regenerate the wiki Home page from the
   committed ledger. See [`tools/wiki/README.md`](tools/wiki/README.md).
8. **Cleanup:** delete the branch.

### The Quality codes (matching state)

Function state lives in `data/lcuswitch_functions.csv`. Quality codes:
`U` (unknown), `O` (OK / verified matching), `M`/`m` (partial), `W`. **CI
rejects any `W`-state function** — never commit one. `tools/check` is the
objective verifier; `python3 tools/common/progress.py` shows overall progress.

### Escalating blockers (the advisor)

Some functions do not yield to normal iteration — the reconstruction is
functionally correct but a diff persists that is a pure compiler artifact
(instruction scheduling, register-reuse, a value hoisted/sunk across a branch),
or matching needs something outside the plain-C loop (a specific data symbol, an
inline-asm idiom, an ABI detail). **Do not force these and do not commit a `W`
state.**

**Default path — spawn the advisor subagent.** The implementing agent spawns an
**analysis-only advisor** ([`.claude/agents/advisor.md`](.claude/agents/advisor.md))
with the `Agent` tool (`subagent_type: advisor`). It is an empty-context Opus
agent at max reasoning effort with **read-only tools** (Read/Bash/Grep/Glob, no
Edit/Write) — structurally it *cannot* implement, it only advises. Give it in the
spawn prompt: (a) the blocker concretely, (b) the target disassembly + the exact
source you tried + the verbatim `tools/check --always-diff` residual, (c) example
functions/addresses, (d) numbered questions, and (e) what you already ruled out
so it does not re-derive. It returns a verdict (bit-exact / functional /
tooling-fix / genuine-limit) + a concrete fix + ruled-out dead ends straight to
you. **Implement proof-first** (reconstruct → `tools/check` → commit as its own
PR), then continue. If it only partly resolves the blocker, gather fresh
measurement data + new numbered questions and **spawn the advisor again** — it
always reads the latest hand-off state first. The loop never stalls and the main
agent's context is not burdened by the heavy analysis.

> A larger, self-contained blocker (a whole hard function or family) can also be
> handed to a general-purpose Opus subagent that **iterates the build/`check`
> loop itself** and returns matching source — the advisor reasons; a
> general-purpose subagent can also grind. Both keep the main context clean.

**Fallback path — labelled issue + external advisor.** When you want the
claude.ai advisor (historically **Fable**, `claude-fable-5`) or a separate
maximum-effort Opus session on the heaviest problems, or when subagent capacity
is rate-limited, escalate via a GitHub issue instead:

1. Leave the function unchanged at its honest state (`U`/`M`/`m`) — revert any
   hacky non-matching attempt so the tree stays clean. If `tools/check` bumped
   the function to `W` while you were iterating, reset it to its honest state in
   `data/lcuswitch_functions.csv` before you finish (CI rejects `W`).
2. Open a GitHub issue and label it **`fable`**. Title it for the function
   (e.g. `NuVecNormEx — store scheduling won't converge`). Because step 1 leaves
   the tree clean, Fable **cannot read your attempt from `src/`** — the issue
   body is the only record, so it must be self-contained. Include, at minimum:
   - the **acceptance criterion**: the mangled symbol(s) so Fable can run
     `tools/check <sym>` = OK;
   - the function's **semantics** (what it computes, values → offsets);
   - the **exact source you tried**, pasted in full in a fenced block (not a
     description of it) — plus any variants you already ruled out, so Fable does
     not re-tread them;
   - the **verbatim `tools/check --always-diff` hunk** — the literal, unabridged
     TARGET-vs-CURRENT output (strip only the ANSI colour codes). Do **not**
     hand-summarise or elide rows: the `CURRENT` column must be present so Fable
     sees your exact codegen without recompiling (its prompt forbids build
     loops). Capture it *before* you revert in step 1, or briefly re-apply the
     source to regenerate it.

   The target disassembly Fable pulls itself from `data/main.elf`; everything
   else above it needs from you.
   Then post a **handoff comment** led with `🟣 FABLE HANDOFF` — a one-line status
   + the specific ask (e.g. "solve this" / "lever for the residual, or confirm
   M?"). This marks the issue as awaiting Fable; the batch relay (below) acts on
   exactly these and skips concluded ones.
3. **Fable** (the `claude-fable-5` model) monitors `fable`-labelled issues and
   **comments** with candidate approaches. Fable **does not implement** — it only
   analyses and suggests. Drive Fable with the ready-made prompt in
   [`docs/FABLE_PROMPT.md`](docs/FABLE_PROMPT.md): either the single-issue block
   (fill in the issue number) or the **Batch mode** block (relays every issue
   with a pending `🟣 FABLE HANDOFF` at once). Both keep Fable read-only and
   token-frugal.
4. Pick the issue back up: implement Fable's suggestion, verify with
   `tools/check`, and if it matches, close the issue in the merge that lands the
   fix (`Closes #NN`). If a suggestion doesn't pan out, re-ping the same issue
   with a fresh `🟣 FABLE HANDOFF` + the new residual and keep it open.

The `fable` label is the hand-off boundary: agents doing implementation open and
consume these issues; Fable only advises on them.

---

## 5 · The function matching loop

Per function (see [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md)):

1. Understand the target function in IDA Pro or Ghidra (see
   [`docs/DECOMPILERS.md`](docs/DECOMPILERS.md)). Rename variables, fill in
   structs. Do not paste decompiler pseudocode verbatim.
2. Reimplement it in clean C++ under `src/`, staying close to the original.
3. Build: `python3 tools/build.py`.
4. Verify: `tools/check`. It diffs your object against the original binary.
5. Not matching → iterate on the diff. Share a scratch with
   `tools/decompme <Function Name>` when useful.

Bit-for-bit matching is the goal. Match idioms already in the tree
(`__attribute__((noinline))`, deliberate `goto`, manual bit-twiddling,
offset-annotated structs) are documented by example in existing `src/` files —
follow them; do not invent new ones.

---

## 6 · Directories

| Path | Contents |
|---|---|
| `src/` | Reconstructed C++, organized by original engine subsystem (`chroma`, `edlevel`, `edtools`, `kestrel`, `legoapi`, `legogame`, `nu2api`, `nu3d`, `nucore`, `numath`, `support`). Mirrors demangled symbols. |
| `data/` | Ground-truth: `lcuswitch_functions.csv` (function states), `java_class_map.yaml`, symbol data. |
| `lib/` | Headers: `nnheaders` (Switch SDK), aarch64 support. |
| `tools/` | `setup.py`, `build.py`, `check`, `listsym`, `decompme`, `lint.py`, `common/` (nx-decomp-tools submodule). |
| `toolchain/` | Pinned Clang 3.9.1 + musl sysroot + `ToolchainNX64.cmake` (all downloaded, gitignored). |
| `.devcontainer/` | `devcontainer.json` + `Dockerfile` (Apple Silicon native, pinned toolchain). |
| `.github/workflows/` | CI: build + verify + lint (GitHub Actions). |

---

## 7 · GitHub API

Repo: `alfaiotadev/ezdecomp` @
`https://github.com`. Authenticate with the `GITHUB_TOKEN`
variable from `.env` (never as a literal). Example:

```bash
set -a; source .env; set +a
curl -sS -H "Authorization: token ${GITHUB_TOKEN}" \
  "https://api.github.com/repos/alfaiotadev/ezdecomp/issues?state=open"
```

For git remote operations, inject the token from the environment at runtime only
(never store it plaintext in `.git/config`).
