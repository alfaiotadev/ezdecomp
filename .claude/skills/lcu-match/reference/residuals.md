# Residuals: irreducible `m` vs. fixable — read when it won't go byte-exact

When `tools/check` still shows a diff, the question is: **can source change fix
it, or is it a Clang 3.9.1 artifact no source form can reach?** Answer this fast
so you don't waste the session. Rule of thumb from the whole project history:

> The source-level levers are the **arithmetic DAG, parenthesization, commutative
> operand order, and local declaration order.** Once those are exact and only
> *register numbering / instruction pairing / scheduling* differs, it's an
> irreducible artifact → record `m`, don't grind.

---

## FIXABLE — keep going, change the source

These are real bugs in your reconstruction. Do not accept `m` while any of these
is the cause:

- **`j*4 + j → j*5` fold.** Diff shows a `mul …, #5` or altered index addressing.
  Fix: write the row base as `(j<<2)+j` for range-unknown indices (see idiom 8).
- **`fmaxnm`/`fminnm` where the target has `fmax`/`fmin` (or vice-versa).** You
  used `fmaxf`/`fminf`; the target used a ternary clamp — or the reverse. Fix:
  switch the spelling (idiom 7).
- **Commutative operand order** — diff is identical ops but `fmul s,a,b` vs
  `fmul s,b,a`. Fix: swap the operands in that source line (idiom 2).
- **FP association** — diff shows adds/muls grouped differently. Fix: add explicit
  parentheses to force `((a+b)+c)` etc. (idiom 3). Clang will NOT reassociate FP,
  so this is fully under your control.
- **A load landing too early/late**, or an extra reload from aliasing. Fix:
  compute-into-locals-then-store (idiom 1), read a pointer's fields into locals
  once, or use the `if(out==lhs||out==rhs)` two-path (idiom 9). Splitting a
  statement can move a load past an op (idiom 10).
- **Wrong `sqrt` guard shape / `fabs` spelling / div-by-zero form** — use the
  exact idiom the target shows (idioms 4–6).

## IRREDUCIBLE — record `m`, escalate only to confirm

Arithmetic is exact; only the following remain. No source form reliably reaches
these under Clang 3.9.1 — they are register-allocator / scheduler tie-breaks:

- **RAGreedy register-number tie-breaks** — e.g. target uses `d12/d13` where you
  get `s3/s4`, correlated pairs swapped, sometimes with a store-order knock-on.
  (Seen on `NuQuatSlerp`, `NuQuatFromEulerRadsXYZ`, `NuQuatFromEulerXYZ` — some
  cost 1000s of blind variants and still didn't resolve.) The purest form:
  **identical instruction order, only a consistent register relabeling** (e.g. a
  global `s2↔s5`, `s3↔s4` swap) — a small HFA-sret FP function where the source
  DAG already equals the target and the allocator simply chose an equivalent
  colouring. No source lever touches this. (`NuKDOPBase::ClosestPointOnPlaneToOrigin`
  — advisor claimed the verbatim source would match; a build proved it does not,
  confirming a genuine colouring tie-break.)
- **GenericScheduler / machine-scheduler `ldp`/`ldr` slot placement** — the same
  loads, paired or ordered differently. (`NuVecMtxTransformVU0`, `NuQuatNormalise`.)
- **Load-clustering** — target pairs `ldp (h,i)` but codegen pairs `(g,h)`,
  cascading into register renames. (`NuMtxInvTranspose3x3`, `NuMtxInvRSS`.)
- **InstCombine commutative-fmul canonicalization interacting with the scheduler**
  in a tail you can't reorder from source. (`NuMtxInvVU0`, `NuMtxOrth`.)
- **Store-merge + fadd schedule** artifacts in quaternion→matrix builders.
  (`NuMtxSetRotationAxisOld`.)
- **Rematerialization / redundant reloads** the RA inserts a fixed number of, that
  C source can't dictate (instr count straddles the target). (`NuMtxMul` family.)
- **Narrow-load + wide-extract hybrid** (integer, not FP/RA) — target does a
  32-bit `ldr w8` **then** a 64-bit `ubfx x8, x8, #k, #1` on the zero-extended
  value (a bit test on a `>>k & 1` field). Neither reachable source form matches:
  a 32-bit-typed field gives `ubfx w8` (InstCombine sinks the shift under the
  `zext` via `lshr(zext X,C)->zext(lshr X,C)` when `k<32`, re-typing the extract
  to i32); a 64-bit-typed load (pointer-cast to force i64) gives the wanted
  `ubfx x8` **but keeps `ldr x8`** (Clang 3.9.1's `ReduceLoadWidth` does not
  narrow it). The target's `ldr w8`+`ubfx x8` needs the load narrowed while the
  i64 extract is retained — a DAG-combine state no single-TU source spelling
  reaches. Both `ubfx w`/`ldr x` residuals are functionally identical → `m`.
  (`VehicleAction_OnScreen::VehicleExec` — advisor + build confirmed both branches
  are the only reachable outputs.)

When you're here: the output is **functionally identical**, the reconstruction is
**correct**, and only codegen noise differs. That is a legitimate `m`. Confirm
with the advisor (it will say `functional` / `genuine-limit`), then move on.
**Never** downgrade to `W`, and never fake a match.

## Fast triage checklist
1. Is the set of instructions (the multiset) the same as the target? If NO → your
   arithmetic/DAG is wrong; it's fixable, keep reconstructing.
2. If the multiset matches but order/registers differ → walk the FIXABLE list
   above; try each applicable source lever once.
3. Still only reg/scheduling noise after those → it's IRREDUCIBLE → `m` + escalate
   to confirm (see `workflow.md`).
