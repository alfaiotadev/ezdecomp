// Engine umbrella context for seeding U-function decomp.me scratches.
//
// This file is NOT part of the game build (not in CMakeLists) — it is a decomp.me
// CONTEXT donor: a broad, co-compiling set of engine headers whose types cover the
// nucore / nu3d / numath / support / legoapi U-function families. tools/decompme -s
// <this file> gives an unimplemented (U) function a working context + the target asm
// so a contributor writes only the function body. Clusters that CONFLICT with these
// headers (e.g. the kestrel ActionInstanceData cluster, which redefines NuCore) need
// their own umbrella. See docs/AUTOMATION.md.
//
// At runtime the seeding rig keeps a copy OUTSIDE the git-cleaned worktree
// (/home/decomp/umbrella_engine.cpp) so the autoloop's `git clean` can't delete it.
#include "numath/types.h"
#include "numath/scalar.h"
#include "numath/vector.h"
#include "numath/matrix.h"
#include "numath/quaternion.h"
#include "numath/random.h"
#include "nucore/nucore.h"
#include "nucore/NuFile.h"
#include "nucore/NuString.h"
#include "nucore/NuThreadBase.h"
#include "nucore/NuThread.h"
#include "nucore/NuPvs.h"
#include "nucore/NuVideo.h"
#include "nucore/NuCheckSum.h"
#include "nucore/NuSerialize.h"
#include "nucore/NuLocaleManager.h"
#include "nu3d/NuRender.h"
#include "nu3d/NuRenderObject.h"
#include "nu3d/NuDisplayScene.h"
#include "support/CommonString.h"
#include "legoapi/BoxGeom.h"
