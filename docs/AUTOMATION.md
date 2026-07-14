# Maintainer automation rig

How the crowdsource board is fed and drained. Two lanes feed the same issues/PRs:

- **Humans** — browser + decomp.me. Pick an `open` issue, iterate its scratch to 100%,
  open a PR with the scratch link. (decomp.me compiles + diffs server-side; no binary.)
- **Autonomous agents** (e.g. Kimi K2.7 via the Devin CLI) — can't use decomp.me
  (its `/compile` API is Cloudflare-blocked for non-browser clients), so they match
  **locally** with `tools/check` (needs the binary) and a bot lands the result.

All the maintainer tooling lives in `tools/` here; it runs inside the decomp
devcontainer (needs the binary + Clang 3.9.1). Contributors never need any of it.

## Scripts

| Script | Role |
|---|---|
| `tools/seed_scratches.py` | Enumerate `M`/`U` functions, create a public decomp.me scratch per function (via `tools/decompme`), open a `good-first-function` issue linking it. Never seed `m` (irreducible/optimal — not a task). |
| `tools/crowdship.py` | Land an agent's local byte-match: re-verify `tools/check` == OK, copy the changed src (+ CSV) into a PAT-authed ezdecomp clone, PR + squash-merge (`Closes #issue`). |
| `tools/crowd-autoloop.sh` | Drain the board: for each open matchable issue, run a fresh Kimi to match it locally, then `crowdship`. Resets the worktree between issues. |
| `tools/umbrella_engine.cpp` | decomp.me **context** donor for U functions in the engine cluster (nucore/nu3d/numath/support/legoapi). |
| `tools/ensure_umbrella_ctx.py` | Re-append the umbrella's `compile_commands.json` entry (cmake wipes it on reconfigure). |

## One-time container setup (the seeding rig)

`tools/decompme` (upstream) only seeds functions that are already in the build — it
filters candidates by the decomp ELF's symbol table, so untouched `U` functions fail
with `no match`. To seed `U`, apply a one-line patch and rebuild:

1. In `tools/common/viking/src/tools/decompme.rs`, replace the
   `filter_candidates_by_symtab(...)` line with
   `let filtered_functions: Vec<&functions::Info> = functions.iter().collect();`
   (use ALL functions, not just symtab-present ones).
2. Build deps: `rustup` (minimal), `pkg-config libssl-dev`, and
   `clang-18 libclang-common-18-dev` (bad64-sys' bindgen needs clang builtin headers;
   `export BINDGEN_EXTRA_CLANG_ARGS=-I$(dirname $(find /usr/lib/llvm-18 -name stdbool.h))`).
3. `export LIBCLANG_PATH=/usr/lib/aarch64-linux-gnu` (libclang1-18) — also lets
   `tools/decompme` move the target function into the scratch's source tab.
4. `cargo build --release --bin decompme` in `tools/common/viking`, then install it over
   `toolchain/bin/decompme` (keep the original as `decompme.orig`).

Keep `umbrella_engine.cpp` OUTSIDE the worktree at `/home/decomp/umbrella_engine.cpp`
(the autoloop's `git clean` deletes untracked files in `src/`), and run
`ensure_umbrella_ctx.py` after any build to restore its compile_commands entry.

## Usage

```bash
# seed one cluster's U functions (engine umbrella + a matching name filter)
python3 tools/ensure_umbrella_ctx.py
GITHUB_TOKEN=$ALFAIOTADEV_GH_PAT python3 tools/seed_scratches.py \
  --quality U --u-context-source /home/decomp/umbrella_engine.cpp \
  --name-filter '^_Z[0-9]+(NuFile|NuString|NuPvs|NuVideo|NuRender|NuSerialize|...)' --limit 15

# drain the board autonomously
CROWD_MAX=40 CROWD_ITER_TIMEOUT=25m nohup bash tools/crowd-autoloop.sh \
  > /home/decomp/crowd-autoloop.main.log 2>&1 &
```

## Gotchas

- **`git clean` / worktree resets wipe untracked files** — keep runtime artifacts
  (umbrella, seeder, bot) under `/home/decomp/`, not in the worktree.
- **A cluster umbrella can't cover everything** — reconstructed headers conflict across
  clusters (e.g. `nucore.h` vs kestrel `ActionInstanceData.h` both define `NuCore`).
  Build one umbrella per co-compiling cluster.
- **Match difficulty tiers** — small U/M functions match ~78% one-shot; the hard tail
  (float math, scheduling artifacts) needs more iterations / a stronger model / the
  advisor. `m` = irreducible; not a task.
- **decomp.me API** — scratch *create* (`POST /api/scratch`) is not CF-challenged;
  *compile* and page GETs are. Agents therefore verify with local `tools/check`.
