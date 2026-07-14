#include "nu3d/NuCutScene.h"

void (*NuCutSceneResetCharactersFn)(instNUGCUTSCENE*);

void NuSetCutSceneResetCharactersFn(void (*fn)(instNUGCUTSCENE*)) {
    NuCutSceneResetCharactersFn = fn;
}
