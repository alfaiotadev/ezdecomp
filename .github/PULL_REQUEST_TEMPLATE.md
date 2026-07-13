<!--
  PR title convention:
    Implement <Name>   — a matching (100%) implementation
    Work on <Name>     — partial / non-matching progress
    Complete <Name>    — finishing a class or method
-->

## Function(s)

<!-- Mangled symbol(s) from data/lcuswitch_functions.csv this PR touches. -->

- `_ZN...`

## Match proof (required for "Implement")

<!--
  Public CI only compiles + lints — it does NOT byte-verify (no binary in public CI).
  Proof of a byte-exact match is a decomp.me scratch showing 100%. Paste the link:
-->

- decomp.me scratch: https://decomp.me/scratch/xxxxx  (diff: 100%)

## Quality state

<!-- The CSV Quality column this sets. O = byte-exact, m = irreducible codegen artifact. -->

- [ ] `O` (byte-exact)
- [ ] `m` (functionally identical, minor irreducible diff — explain below)

## Checklist

- [ ] Ran `tools/lint.py` (clang-format clean)
- [ ] Source is in the correct `src/<subsystem>/` directory
- [ ] Not committing any `W` (work-in-progress) state
- [ ] No game data / binary / secrets added

<!--
  The maintainer's import bot re-verifies the match privately with `tools/check`
  before merge. If your scratch is 100% and the source is clean, that will pass.
-->
