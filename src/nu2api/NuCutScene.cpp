#include "nu2api/NuCutScene.h"

void NuSetCutSceneDestroyCharactersFn(void (*fn)(NuCutSceneRaw*)) {
    NuCutSceneDestroyCharacters = fn;
}
