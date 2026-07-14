#pragma once

#include "numath/types.h"

struct NuCutSceneRawRigid;

extern void (*NuCutSceneRigidCollisionCheck)(NuCutSceneRawRigid*, NUMTX*);

void NuSetCutSceneRigidCollisionCheckFn(void (*fn)(NuCutSceneRawRigid*, NUMTX*));
