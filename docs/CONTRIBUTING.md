# Contributing

There are two ways to contribute. **Most people should use the browser path** — it
needs no game binary, no toolchain, and no local setup.

---

## Path A — In the browser, with any LLM (recommended, zero setup)

This is the whole point of the project: you can produce a byte-exact match without
owning the game or installing anything. [decomp.me](https://decomp.me) compiles and
diffs your code **on its server** against the target.

1. **Pick a task.** Browse the [open issues](https://github.com/alfaiotadev/ezdecomp/issues?q=is%3Aissue+is%3Aopen+label%3Aopen)
   (label `open` / `good-first-function`). Each issue links a ready-made **decomp.me
   scratch** with the target assembly, context, and exact compiler flags baked in.
2. **Claim it** so nobody duplicates your work: comment `/claim` on the issue.
3. **Open the scratch link.** You'll see the target assembly on the right and an
   editor on the left. Write the function in C++ (paste it to your favourite LLM,
   ask it to match the target asm — iterate).
4. **Match it.** Every time you edit, decomp.me recompiles and shows the diff.
   Your goal is **100%** (the diff turns green / score 0).
5. **Submit.** Open a pull request that adds your source under the right
   `src/<subsystem>/` directory, and **paste the 100% scratch link** in the PR
   (the PR template asks for it). That link is your proof of a match.

That's it. A maintainer bot re-verifies the match privately and merges.

> **Why the scratch link is the proof:** the public CI only *compiles* and lint-checks
> — it can't byte-verify, because that needs the copyrighted binary, which is never
> in this repo or CI. A 100% decomp.me scratch is the objective proof instead.

### Tips
- Small, straight-line functions match fastest — start there.
- The function name usually tells you what it does; you rarely need deep game knowledge.
- Stuck? Ask in the [Discord](https://discord.com/invite/AyFjHz5EaT). General decomp
  technique: [botw.link/contribute](https://botw.link/contribute) and the
  [cheatsheet](https://botw.link/cheatsheet).
- Truly won't converge (a pure compiler artifact)? Open a
  [🟣 Fable escalation](https://github.com/alfaiotadev/ezdecomp/issues/new?template=fable-escalation.yml)
  issue with your scratch and the residual diff.

---

## Path B — Local, byte-verified (power users)

If you have your own legal dump of the game you can run the full matching loop
locally and byte-verify with `tools/check` before submitting.

1. Set up the project per [docs/BUILDING.md](BUILDING.md), then run `tools/check` to
   confirm the setup.
2. Pick a function; understand it (IDA Pro / Ghidra help — rename vars, auto-fill
   structs). Don't paste raw pseudocode; write clean C++.
3. `python3 tools/build.py`, then `tools/check <symbol>` — iterate until it prints `OK`.
4. Open a PR (a scratch link is still welcome but not required if `tools/check` is `OK`).

---

## Pull requests

Name the PR:
- **Implement `Name`** — a matching (100%) implementation
- **Work on `Name`** — partial / non-matching progress
- **Complete `Name`** — finishing a class or method

Before submitting, run `tools/lint.py` so your files match the repo's clang-format
style (`--fix` to auto-fix, `--format` to run clang-format, `--find-unsorted` to find
unsorted classes/enums). **Back up first — the linter is experimental.**

Public CI (GitHub Actions, [`.github/workflows/`](../.github/workflows)) runs on your
PR: it builds the project and checks clang-format. It does **not** byte-verify (see the
note above). PRs are squash-merged, so don't stress over individual commits.

## Info

The project is early — guidelines will evolve as we learn more about the game's
internals. When in doubt, ask on Discord.
