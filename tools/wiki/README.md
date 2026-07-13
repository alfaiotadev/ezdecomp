# tools/wiki — decomp progress board

[`gen_progress.py`](gen_progress.py) regenerates the wiki **Home** page — an
ASCII progress board (overall coverage, match quality, per-subsystem breakdown,
phase status) — entirely from committed repo state
(`data/lcuswitch_functions.csv`, the per-function match ledger). The
per-subsystem bars additionally map each matched symbol to its
`src/<subsystem>/` directory via `nm` over the objects in `build/`, so run
`tools/build.py` first for that section (the board still renders without it).

Keeping the board current is part of the standard workflow (AGENTS.md §4): after
a function-match PR merges to `master`, the matched-function count changes, so
refresh the board.

```bash
# after a function-match merge (on up-to-date master, with a build present):
tools/build.py                           # so the subsystem map is available
set -a; source .env; set +a
tools/wiki/gen_progress.py --push        # regenerate + update wiki Home page
# or preview first:
tools/wiki/gen_progress.py               # print markdown to stdout
```

`--push` reads `GITHUB_TOKEN` (and optionally
`GITHUB_API_URL`/`GITHUB_OWNER`/`GITHUB_REPO`) from the environment; the token is
only ever sent in the Authorization header, never printed. It PATCHes the
existing Home page or creates it if absent.

Everything on the board is computed from the repo (the ledger CSV plus the total
function/byte count of the target NSO, which is a fixed property of EU v1.0.3),
so the board never drifts from `master`.
