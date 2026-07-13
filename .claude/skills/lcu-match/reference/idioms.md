# House-style idioms (read before reconstructing)

These are not style preferences — **they change the output bytes.** Clang 3.9.1
at `-O3` is deterministic, so struct layout, operand order, parenthesization, and
even local-declaration order steer register allocation and scheduling. Match the
existing tree; do not invent new spellings.

Ground truth for all of this: `src/numath/` (the most heavily matched subsystem).
Open the neighbours of the file you're editing and copy their conventions.

---

## Types & memory layout (`src/numath/types.h`)
Plain C structs, no methods, no alignment attributes. **The offsets are exactly
what the disassembly addresses** — get the layout right or nothing matches.

```cpp
struct NUVEC   { float x, y, z; };          // offsets 0,4,8
struct NUVEC4  { float x, y, z, w; };        // 0,4,8,12
struct NUQUAT  { float x, y, z, w; };        // w is LAST, even when math lists w first
struct NUMTX   { float m[4][4]; };           // row-major; flat elem = m[row*4+col]
struct NUPLANE { NUVEC normal; float d; };
struct NUANGVEC{ int x, y, z; };             // integer angles
```
**HFA return convention:** a function returning `NUVEC` returns 3 floats in
v0/v1/v2 (not via the out-pointer). If the epilogue writes s0/s1/s2 and there's
no store through x0, the return type is a value struct, not `void … (out*)`.
(`NuMtxNormalise` even keeps a *wrong* declared `bool` return because the mangled
name is unaffected and the float epilogue is what matters.)

## File shape
- Includes are quoted in the `.cpp` (`#include "numath/vector.h"`); `<math.h>`
  only where raw `sqrtf` is used.
- **No namespace.** Free C-style functions with the exact `Nu…` names.
- Signature order: **out-pointer first, then `const*` inputs, scalars last.**
  `void NuMtxMul(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs)`.
- **East `const`**: `NUMTX const*`, not `const NUMTX*` (the tree is mostly east;
  a few slips exist — follow the file you're in).
- Access members **explicitly per component** (`out->x`, `->m[i][j]`). Never
  loops or `memcpy` for small fixed-size ops.

---

## Core idioms (each shifts the codegen — use the one the target shows)

**1. Compute all results into locals, then store.** Deferring stores to the end
reproduces the target's store scheduling. Note `NuVecCross` even computes in
`y, z, x` order:
```cpp
void NuVecCross(NUVEC* out, NUVEC const* v1, NUVEC const* v2) {
    float y = v1->z * v2->x - v1->x * v2->z;
    float z = v1->x * v2->y - v1->y * v2->x;
    float x = v1->y * v2->z - v1->z * v2->y;
    out->x = x; out->y = y; out->z = z;
}
```

**2. Deliberate commutative operand order.** The same expression is written
`a*b` on one line and `b*a` on the next — on purpose, to match InstCombine's
canonicalization in the target. `NuVecNormEx`:
```cpp
out->x = x * invMag;
out->y = invMag * y;   // swapped
out->z = z * invMag;
```
When only the operand order of a commutative `fmul`/`fadd` differs in the diff,
**flip the source operands** and re-check.

**3. Explicit parenthesization pins FP association** (no `-ffast-math`, so the
compiler won't reassociate). Matrix multiply groups left-to-right explicitly:
```cpp
float m00 = (l00*r->m[0][0] + l01*r->m[1][0]) + l02*r->m[2][0];
```
Quaternion doublings are `(xy + xy)`, never `2.0f*xy`.

**4. Guarded normalize — two accepted spellings; pick the one the target shows:**
```cpp
// (a) guard the squared magnitude, raw sqrtf:
if (sq <= 0.0f) invMag = 0.0f; else invMag = 1.0f / sqrtf(sq);
// (b) NuFsqrt first (scalar.h: f<=0?0:sqrt(f) — note double sqrt), then guard mag:
float mag = NuFsqrt(...); if (mag > 0.0f) invMag = 1.0f/mag; else invMag = 0.0f;
```

**5. Divide-by-zero guard ternary:** `x == 0.0f ? 0.0f : 1.0f/x`  (e.g.
`det != 0.0f ? 1.0f/det : 0.0f`).

**6. Manual `fabs` — never call `fabsf`:** `v >= 0.0f ? v : -v`. (`fabsf` lowers
differently.)

**7. NaN-propagating clamp — a ternary, NOT `fmaxf`/`fminf`:**
```cpp
sp = sp < -1.0f ? -1.0f : sp;
sp = sp >  1.0f ?  1.0f : sp;
```
`fmaxf`/`fminf` emit `fmaxnm`/`fminnm` (NaN-quieting); the ternary emits plain
`fmax`/`fmin` (NaN-propagating). Match whichever the disasm shows.

**8. Flat matrix index with a shift for range-unknown indices** — to dodge
InstCombine's `j*4 + j → j*5` fold that would change the addressing:
```cpp
const float* mf = &mtx->m[0][0];
float s = NuFsqrt(mf[i*4+i] - (mf[(j<<2)+j] + mf[(k<<2)+k]) + 1.0f);
```
Use `i*4` for a known-range index (folds to `bfi`); use `(j<<2)+j` for
table-derived `j,k` (keeps `lsl+add`).

**9. Aliasing two-path for big ops that write their own input** —
`if (out == lhs || out == rhs)` selects a compute-all-to-locals path; the else
branch writes as it computes. Both branches must be present
(`NuMtxMul`/`MulR`/`MulH`).

**10. Declaration order of locals = stack-slot / register numbering.** First-
declared local tends to the highest frame slot / lowest register. When only
register *numbers* differ, try reordering your local declarations. You can even
split a computation so a load lands after a prior op:
```cpp
float tr = m00 + m11;
float d22 = m[2][2];   // forces this load after the first fadd
tr = tr + d22;
```

---

## Patterned Exec families — batch cascades (leverage #311)
Big families share one shape: `ActionState Exec(ScriptContext&) override` (and
the `CharacterExec(ApiCharacter*, ScriptContext&)` / `VehicleExec(ApiVehicle*,
ScriptContext&)` variants). Match one canonical representative, then the loop
cascades the rest. The three recurring shapes (all confirmed in disasm):

```cpp
// (a) return-const leaf — the most common, 8 bytes (mov w0,#k; ret):
ActionState X::Exec(ScriptContext&) { return kActionComplete; }   // w0 = 1
// (b) delegate to a base with a bool, tail-call (mov w2,#1; b ExecInternal):
ActionState X::Exec(ScriptContext& c) { return ExecInternal(c, true); }
// (c) one call then return-const (bl helper; mov w0,#1; ret):
ActionState X::VehicleExec(ApiVehicle* v, ScriptContext&) {
    v->TriggerDefaultAutoUpright(); return kActionComplete;
}
```

Family status (Exec-member `U` counts today):
- **`SAction_*`** — proven cascade, already ~half `O` (1,328 done). The reference
  shape; copy an existing `O` SAction `.cpp` (e.g. `SAction_TakeSnapShot`).
- **`CharacterAction_*`** — **untapped, 96 Exec `U`.** Reps: `CharacterAction_IsOn`
  ::Exec (shape b), `CharacterAction_MakeSimpleCharacter`::CharacterExec (shape a).
- **`VehicleAction_*`** — **untapped, 76 Exec `U`.** Rep:
  `VehicleAction_TriggerAutoUpright`::VehicleExec (shape c).
- **`ScrAction_*`** — *not* an Exec cascade: only **one** `Exec` member
  (`ScrAction_ScriptActionBase::Exec`, 188 B, the base). Don't chase it as a family.

Match one rep per family to `O`, confirm the shape here, and let the loop drain
the rest.

## Compiler-generated thunks — never pick standalone
`_ZThn*` symbols are Clang-emitted this-adjust thunks (2,211, all `U`). They are
**not** reconstructable in isolation and must be skipped during candidate
selection — see **`thunks.md`** for the classification and why.

## Blocked on an unknown global?
If a function references a `.data`/`.rodata` address with no name, it can't be
matched until the global is identified. See **`globals.md`** and
`tools/leverage/sweep_unnamed_globals.py` for how to find and name shared globals.

---

## Harvesting idioms for a subsystem you haven't matched in
numath is the proven library; other subsystems (nucore, legoapi, kestrel,
render…) have their own conventions. Before reconstructing there:
1. `grep`/list the `O` (matched) functions in that subsystem's `src/` dir and
   read a few — copy their include style, naming, struct-access, and helper use.
2. Find the subsystem's type headers (under `src/<subsystem>/` or `lib/`) and get
   the struct layouts exactly.
3. Reuse the subsystem's existing helper functions rather than re-deriving math.
