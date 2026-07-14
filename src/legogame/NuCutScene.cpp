#include "legogame/NuCutScene.h"

NuCutSceneCharacterCreateDataFn NuCutSceneCharacterCreateData;

void NuSetCutSceneCharacterCreateDataFn(NuCutSceneCharacterCreateDataFn fn) {
    NuCutSceneCharacterCreateData = fn;
}
