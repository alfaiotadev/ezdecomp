#include "nucore/NuCutScene.h"

extern void (*NuCutSceneFindCharacters)(NuCutSceneRaw*, void*);

void NuSetCutSceneFindCharactersFn(void (*param_1)(NuCutSceneRaw*, void*)) {
    NuCutSceneFindCharacters = param_1;
}
