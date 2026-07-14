#include "nu2api/NuCutScene.h"

long (*NuCutScenePTLFixUp)(const char*, NuCutSceneRaw*, void*);

void NuSetCutScenePTLFixUpFn(long (*fn)(const char*, NuCutSceneRaw*, void*)) {
    NuCutScenePTLFixUp = fn;
}
