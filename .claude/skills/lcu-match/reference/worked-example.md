# Worked example — one full match, disasm → `O`

Read this first if you've never matched here. It walks the entire 7-step loop for
one real, already-matched function (`NuVecCross`, `src/numath/vector.cpp`) so you
can imitate the shape rather than reason from scratch.

---

## Step 1 — Pick
`NuVecCross` — 64 bytes, straight-line, numath. A good easy target.

## Step 2 — Disassemble the target
```bash
python3 tools/dc.py disasm _Z10NuVecCrossP5NUVECPKS_S2_
```
Output:
```
=== _Z10NuVecCrossP5NUVECPKS_S2_  (0x34ef1c, 64 bytes, quality O) ===
  34ef1c: ldp   s1, s2, [x2]        ; v2->x, v2->y
  34ef20: ldr   s4, [x2, #8]        ; v2->z
  34ef24: ldr   s5, [x1]            ; v1->x
  34ef28: fmul  s16, s5, s4         ; v1->x * v2->z
  34ef2c: fmul  s5,  s5, s2         ; v1->x * v2->y
  34ef30: ldp   s6, s0, [x1, #4]    ; v1->y, v1->z
  34ef34: fmul  s3,  s0, s1         ; v1->z * v2->x
  34ef38: fsub  s3,  s3, s16        ; (v1->z*v2->x) - (v1->x*v2->z)   = y
  34ef3c: fmul  s16, s1, s6         ; v2->x * v1->y
  34ef40: fsub  s1,  s5, s16        ; (v1->x*v2->y) - (v1->y*v2->x)   = z
  34ef44: fmul  s4,  s4, s6         ; v2->z * v1->y
  34ef48: fmul  s5,  s0, s2         ; v1->z * v2->y
  34ef4c: fsub  s0,  s4, s5         ; (v1->y*v2->z) - (v1->z*v2->y)   = x
  34ef50: stp   s0, s3, [x0]        ; out->x = x, out->y = y
  34ef54: str   s1, [x0, #8]        ; out->z = z
  34ef58: ret
```
Decode it:
- x0 = out, x1 = v1, x2 = v2 (out-ptr first, per the signature convention).
- Three cross-product components computed as fsub of two fmuls each.
- The **stores** are `out->x, out->y` then `out->z` — but the computation order in
  the body is **y first, then z, then x** (see the fsub sequence). That ordering
  is what we must reproduce.

## Step 3 — Reconstruct (after reading `idioms.md`)
Apply idiom 1 (compute into locals in the target's order, then store) and the
per-component offset access. The committed source in
`src/numath/vector.cpp`:
```cpp
void NuVecCross(NUVEC* out, NUVEC const* v1, NUVEC const* v2) {
    float y = v1->z * v2->x - v1->x * v2->z;
    float z = v1->x * v2->y - v1->y * v2->x;
    float x = v1->y * v2->z - v1->z * v2->y;
    out->x = x;
    out->y = y;
    out->z = z;
}
```
Why this exact form:
- Locals declared `y, z, x` in that order → matches the target's compute order and
  register numbering.
- Each expression's operand order (`v1->z * v2->x`, etc.) matches the `fmul`
  operands in the disasm — don't swap them here.
- Storing `out->x/y/z` at the end (not as computed) lets Clang emit the
  `stp/str` pair at the bottom like the target.

## Step 4 — Build
```bash
python3 tools/build.py
```

## Step 5 — Check
```bash
tools/check _Z10NuVecCrossP5NUVECPKS_S2_
```
A byte-exact match prints `OK`. If instead you saw a diff, you'd compare against
`--always-diff` output and consult `residuals.md` (e.g. if the only difference
were `fmul s16,s5,s4` vs `fmul s16,s4,s5`, you'd swap that source line's
operands).

## Step 6 — Set the state
`OK` → byte-exact → `O`:
```bash
python3 tools/dc.py setstate _Z10NuVecCrossP5NUVECPKS_S2_ O
```

## Step 7 — Finish
Default: `python3 tools/lint.py --format`, confirm no `W` in the CSV, leave the
tree clean, and hand off (report the `O`). Only if explicitly asked to ship,
follow the SHIP section of `workflow.md`.

---

**The lesson:** you did not "solve" the cross product from math — you *read the
target's operation order, operand order, and store order straight out of the
disassembly* and wrote the minimal C++ that reproduces it. That is the whole job.
Decode → write → build → check. Don't over-think; get to `check`.
