#include "nucore/NuCutScene.h"

void NuSetCutSceneRigidCollisionCheckFn(void (*fn)(NuCutSceneRawRigid*, NUMTX*)) {
    NuCutSceneRigidCollisionCheck = fn;
}
