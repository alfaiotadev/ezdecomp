# `_ZThn*` thunks — do not pick these as standalone targets

**Rule of thumb:** if a CSV `Name` starts with `_ZThn`, **skip it** during
candidate selection. It is never a standalone win. Do not open a PR for a bare
thunk.

## What they are
All 2,211 `_ZThn*` rows are Itanium **non-virtual this-adjusting thunks**
(entered via a secondary-base vtable slot). This binary has **zero** `_ZTv`
(virtual) and **zero** `_ZTc`/`_ZTch` (covariant) thunks. The CSV names are
correct (read from `.dynsym`), even when the body looks like a full function.

Clang 3.9.1 **emits these automatically** from the class's vtable when a base
sits at a non-zero offset (multiple inheritance / secondary base with a vptr).
**We never hand-write a thunk.** You cannot make a standalone `.cpp` emit
`sub x0,x0,#N ; b target`.

## The four shapes you will see (classify by size + disasm)
- **size 4** — lone `b target`. The adjust was elided (target ignores `this`,
  e.g. a factory; or it tail-merged into a base dtor at the same subobject).
- **size 8** — `sub x0,x0,#off ; b target`. The 598-row bulk; ~386 are D0/D1.
- **size ≥36 with a real prologue + `bl`s** — a genuine **deleting destructor
  (D0)** / base D1 / factory body that merely carries a thunk name; the adjust
  is folded into an early `sub x19,x0,#off` (or elided entirely).

## Why they are not standalone-matchable
- `sub x0,x0,#off` is a constant (position-independent) — matches once the base
  offset in your struct layout is right.
- `b target` is a **PC-relative displacement** = `target-(thunk+4)`. It matches
  only when the target sibling/base function is placed at the original relative
  offset — often a base dtor in **another TU**, so the linker + TU ordering
  decide it. A thunk therefore resolves *last*, as a byproduct of the class.

## What to do
- **Selection:** filter out `^_ZThn` from the U-candidate list (see the `awk`
  predicate in `choosing.md`). They are not fast wins and burn the loop.
- **When reconstructing a whole class:** write the class's real virtual methods
  and destructors (D0 deleting dtor = `~T(); NuMemoryManager::BlockFree(this,0)`
  via `NuMemory::GetThreadMem()`, house style). Declare the correct
  multiple-inheritance so Clang emits the thunks itself; verify the size-4/size-8
  thunk rows **last**, after the target is placed. Do not hand-write them.
- **Never** mark a thunk `m`/`W` on thunk grounds — it is deferred layout work,
  not a compiler artifact.

_Source: analysis of `data/main.elf` for GitHub leverage issue #312 (all size
buckets grounded in disasm; covariant/virtual thunk classes confirmed absent)._
