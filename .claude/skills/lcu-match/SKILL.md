---
name: lcu-match
description: >-
  Match (decompile to byte-identical machine code) a function in this Lego City
  Undercover clean-room decompilation repo. Use whenever the task is to
  implement, match, decompile, or "work on" a Nu*/engine function against the
  target NSO — it gives the exact pick → disassemble → reconstruct C++ → build →
  verify → set-state loop, the house-style idioms, when to stop and mark `m`, and
  (opt-in) how to ship the PR. Invoke it before touching any `src/**` function.
---

# lcu-match — how to match one function

You are matching decompilation: writing C++ that Clang 3.9.1 compiles to **the
exact same AArch64 bytes** as the original *Lego City Undercover* (Switch) NSO.
This skill is the **procedure**. The *rules* live in `AGENTS.md` / `CLAUDE.md`;
the *live project state* (what's done, what's next) lives in
`SESSION_HANDOVER.md`. Read those for context — but execute the loop below.

This file is deliberately short. It points you to `reference/*.md` files; **read
each one at the moment the step tells you to** (works on any harness with a file
Read tool — do not skip them).

---

## STOP-FIRST rules (breaking one wastes the session)

1. **Never commit `Quality=W`.** CI rejects it. If `check` left a function `W`,
   set it back to its honest state (`O`/`m`/`M`/`U`) before finishing.
2. **Never merge without green CI.** CI is the quality gate, not a formality.
3. **Never invent compile flags.** The toolchain owns them
   (`tools/config.toml` + `toolchain/ToolchainNX64.cmake`). Use `tools/build.py`.
4. **Never `git reset --hard origin/master`.** The `origin/master` ref is stale
   in this container (broken ssh fetch) — it *discards merged work*. Sync to a
   known SHA instead (see `reference/workflow.md`).
5. **Do not think-loop.** The #1 failure mode is burning the whole budget
   reasoning without ever building. After you decode the target: **WRITE source,
   BUILD, run CHECK.** The `check` diff is your source of truth, not your
   reasoning. Get to a real diff within your first few actions.
6. **Never add the game binary / ELF / assets or the `.env` token to git.**
7. **Mind the tools — four moves *look* like a hang and waste the session.**
   (a) `tools/check`, `tools/dc.py`, and everything in `toolchain/bin/`
   are **compiled binaries** — never `head`/`cat`/`less`/`more`/`tail` them
   (you'll dump binary garbage and blow up your context); *run* them, and use
   `tools/check --help` for usage. (b) **Always** give `tools/check` a symbol:
   `tools/check <MangledSymbol>`. **Bare `tools/check` (no argument) checks ALL
   ~26 000 functions** — many minutes, looks frozen. Verify one symbol at a time.
   (c) When `tools/check` finds a diff it opens an **interactive pager** (`less`)
   and STALLS in an agent shell (a `:` / `(END)` prompt, no more output). It
   hardcodes `less`, ignores `$PAGER`, and does NOT check for a tty — so piping
   (`| cat`) does not help. Pass **`--no-pager`**:
   `tools/check <MangledSymbol> --no-pager` (prints the diff and returns).
   (d) Always pass the **full mangled symbol** (from the CSV or `dc.py disasm`),
   never a partial/demangled name like `SAction_Foo` or `SAction_Foo::Exec`. A
   non-unique name makes `check` open an **interactive "did you mean?" prompt**
   that STALLS (it waits on stdin); the exact mangled symbol is unique and
   returns immediately.
8. **Don't over-research the pick.** Choosing a target is a few-second `disasm`
   peek, not an investigation. If a candidate isn't obviously reconstructable
   from its asm, drop it and peek the next — do NOT grep the whole tree hunting
   for classes/headers (that's the same budget-burn as think-looping). See
   `reference/choosing.md`.

---

## The loop (do these in order, every function)

### 1. Pick a function
Start easy so you get a match on the board fast: small (< ~150 bytes),
straight-line, in a subsystem you have idioms for. If unsure which to take, read
**`reference/choosing.md`**.

### 2. Disassemble the target
```bash
python3 tools/dc.py disasm <mangled_symbol>
```
(e.g. `_Z10NuVecCrossP5NUVECPKS_S2_`). This prints the exact target bytes +
instructions. Decode the **formula, operand order, and store order** from it. Do
NOT paste decompiler pseudocode — read the asm and write clean C++.

### 3. Reconstruct clean C++
**First read `reference/idioms.md`** — the house style is load-bearing (struct
offsets, operand order, declaration order all affect the output bytes). Put the
code in `src/<subsystem>/…` mirroring the demangled symbol (e.g. `NuVec*` →
`src/numath/vector.cpp`). Match idioms already in the tree; **do not invent new
ones.** If you've never matched in this subsystem, harvest its conventions first
(see the "Harvesting" section of `reference/idioms.md`).

### 4. Build
```bash
python3 tools/build.py            # add --clean only if the source set changed
```
Fix compile errors before checking. **Never build concurrently** with another
build in `/workspace`.

### 5. Check (this is the truth)
```bash
tools/check <symbol> --no-pager               # byte-diff vs the original; prints OK or a diff
tools/check --always-diff <symbol> --no-pager # show the residual even when it's close
```
**Always pass `<symbol>`** — bare `tools/check` sweeps all ~26 000 functions and
runs for minutes (rule 7b). **Always pass `--no-pager`** — otherwise a diff opens
an interactive `less` that stalls you (rule 7c).

### 6. Judge & set the state
Use this table, then record it:
```bash
python3 tools/dc.py setstate <symbol> <O|m|M>
```

| `check` result | State | Meaning / action |
|---|---|---|
| `OK` (byte-exact) | **`O`** | Done. The only "matched" state. |
| Arithmetic/DAG correct; only register-numbering, instruction-scheduling, or ldp/stp-pairing differs | **`m`** | Functionally identical, irreducible toolchain artifact. Confirm it's truly irreducible (see below), then ship as `m`. |
| Correct-ish but larger structural diff | **`M`** or keep iterating | Reconstruction still off. |
| Wrong output / not yet working | keep **`U`** | **Never** leave it `W`. |

### 7. Finish
- **Default — hand off:** `python3 tools/lint.py --format`, confirm no stray `W`
  in the CSV, leave a clean tree (or a `Work on <Name>` draft PR). Report the
  result and stop. A human / strong model reviews and merges.
- **Opt-in — ship it yourself:** only if the user explicitly asked to ship (or
  passed `--ship`), follow the **SHIP** section of `reference/workflow.md`
  (`dc.py ship …` → PR → wait green CI → squash-merge → wiki).

---

## When to STOP iterating (the anti-thrash guard)

Matching is not "keep trying until perfect." Once the **arithmetic is exact**
(same operations, same FP association) and the diff is *only* register numbering
/ instruction ordering / load-pairing, you have most likely hit an irreducible
Clang 3.9.1 artifact. **Read `reference/residuals.md`** to recognize these fast.

- If the diff is one of the *fixable* patterns (e.g. `j*4+j` fold, `fmaxf` vs a
  ternary, wrong operand order, wrong parenthesization, wrong declaration order)
  → fix the source and re-check. These are real, common, and worth pursuing.
- If, after a handful of focused source-form variants, only reg/scheduling noise
  remains → **mark `m` and escalate to confirm** (below). Do NOT keep spinning
  hundreds of blind variants.

**Hard budget — stop and hand off (byte-exact is NOT required to succeed).**
Especially on a large / float-heavy function: if you have not reached `OK` after
~4–5 build+check iterations, STOP and decide — do not keep grinding, and do not
probe the compiler with throwaway snippets indefinitely:
- Diff is only register-numbering / scheduling / ldp-pairing (same ops, same
  order, size matches) → set **`m`**, escalate to confirm, or hand off the
  residual if you can't escalate. **This is a successful outcome.**
- Diff is still structural (wrong ops / wrong size / extra instructions) → leave
  **`U`** and hand off the `tools/check --always-diff <sym> --no-pager` residual
  for a stronger model.
A big (>~300 B) float-heavy function is often beyond one autonomous pass — a
close, honestly-marked attempt with the residual is the win, not endless
iteration. (Grinding 20+ minutes without stopping is the failure mode.)

## Escalating a blocker
When a function won't match and you can't tell if it's fixable:
- **In Claude Code:** spawn the analysis-only **`advisor`** subagent
  (`subagent_type: advisor`). Give it: the target disasm, the exact source you
  tried, the **verbatim `tools/check --always-diff` residual**, and numbered
  questions. It returns a concrete fix or confirms an honest `m`.
- **On another harness (no advisor):** open a GitHub issue labelled **`fable`**
  with the self-contained residual (see `docs/FABLE_PROMPT.md`).
Details + exact commands: **`reference/workflow.md`**.

---

## Reference files — read them when the step says to
- **`reference/idioms.md`** — house-style C++ patterns (read before step 3).
- **`reference/residuals.md`** — irreducible-vs-fixable diff catalog (read when a
  match won't go byte-exact).
- **`reference/workflow.md`** — `dc.py`/`check`/CSV details, escalation, and the
  full SHIP lifecycle (read for step 7-ship or escalation).
- **`reference/choosing.md`** — how to pick a good next function (read for step 1).
- **`reference/worked-example.md`** — ONE complete match start-to-finish
  (`NuVecCross`). Read this first if you've never matched here before.
- **`reference/thunks.md`** — why `_ZThn*` thunks are never standalone matches
  (read before touching one; the loop should skip them at selection).
- **`reference/globals.md`** — how to identify unnamed `.data`/`.rodata` globals
  (read when a function is blocked on an unknown address).
