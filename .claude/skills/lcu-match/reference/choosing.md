# Choosing a function to match (step 1)

First read `SESSION_HANDOVER.md` — it lists the current state and named NEXT
candidates. Prefer those. If you need to find your own, pick for a fast win.

## What makes a good first/next target
- **Small** — under ~150 bytes (Size column in the CSV). Big functions have more
  scheduling freedom → harder to land byte-exact.
- **Straight-line** — no loops, no complex control flow. Loops (Gauss-Jordan-style
  inverses, convergence loops) are the hard tail; leave them for dedicated passes.
- **In a subsystem you have idioms for** — `numath` is the proven one. If you go
  elsewhere, harvest idioms first (see `idioms.md` → "Harvesting").
- **Self-contained** — doesn't depend on an unidentified `.data` global or on a
  sibling that Clang will inline (single-TU tail-call cases are often
  unmatchable; e.g. `NuVec4ScaleXYZVU0` tail-calls into an inlined sibling).

## Finding untouched (`U`) functions in a subsystem
```bash
# untouched numath functions, smallest first:
awk -F, '$2=="U" && $4 ~ /^_Z.*Nu(Vec|Mtx|Quat)/ {print $3, $4}' \
    data/lcuswitch_functions.csv | sort -n | head -30
```
Adjust the name regex for your subsystem. Decode a candidate with
`python3 tools/dc.py disasm <sym>` and check it's straight-line before
committing to it.

## Always skip these families during selection
- **`_ZThn*` thunks** (2,211 `U`) — compiler-emitted this-adjust thunks, never a
  standalone match. Add `&& $4 !~ /^_ZThn/` to any candidate `awk` predicate.
  See `thunks.md`.
- **Bare tail-call stubs** (`b <…@plt>`) and 4-byte cross-subsystem stubs — see
  the peek rules just below.

## Fastest untapped cascades right now (leverage #311)
`CharacterAction_*` (96 Exec `U`) and `VehicleAction_*` (76 Exec `U`) are the same
`Exec`/`CharacterExec`/`VehicleExec` shape as the already-draining `SAction_*`
family. High hit-rate, patterned. See "Patterned Exec families" in `idioms.md`.
```bash
awk -F, '$2=="U" && $4 ~ /(Character|Vehicle)Action_.*Exec/ {print $3,$4}' \
    data/lcuswitch_functions.csv | sort -n | head
```

## Peek, then commit or skip — in seconds (do NOT research a candidate)
`disasm` each candidate and decide fast. The trap that burns whole sessions is
*investigating* a hard candidate (grepping the tree for its classes/headers)
instead of dropping it. Rule of thumb:
- Body is a lone **tail-call** `b <…@plt>` / `b <label>` (a thunk — e.g. every
  `fnMaths_*` is just `b cosf@plt`) → **skip**. Not a reconstructable match.
- Body is a few straight-line instructions you can read straight into C++ (e.g.
  `orr w0, wzr, #1 ; ret` = `return 1`) → **take it**.
- You can't map the asm to plain C++ in a few seconds, or it needs types you
  can't immediately find → **skip now, peek the next candidate.** Never go
  hunting the tree for a candidate you haven't committed to.

## Easy veins to mine (fast, high hit-rate)
- **`numath`** (`_Z.*Nu(Vec|Mtx|Quat)`) — the proven subsystem: small
  straight-line vector/matrix math. Start here (see `worked-example.md`).
- **Script-action `Exec`/accessors** — `_ZN…SAction_…4ExecER13ScriptContext`
  and small `GetName`/`GetInputs` accessors. Many `Exec`s are literally
  `return <const>` → a one-line, byte-exact match. Highest hit-rate for a first
  win. Find them: `awk -F, '$2=="U" && $4 ~ /SAction_.*4Exec/ {print $3,$4}'
  data/lcuswitch_functions.csv | sort -n | head`.

## What to avoid until you're warmed up
- Functions the handover explicitly flags as **blocked** or **likely unmatchable**
  (e.g. needs an unidentified global, control-flow-heavy, single-TU inlining).
- 4-byte stubs in unrelated subsystems — often single-TU-unmatchable.
- Anything already `O` (done) or `m` (accepted). Check the Quality column first.

## One function at a time
One issue → one branch → one PR. Don't juggle multiple in-flight functions with
`git stash` — that's how a stray `W` row leaks into a commit and fails CI.
