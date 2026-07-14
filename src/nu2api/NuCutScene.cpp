#include "nu2api/NuCutScene.h"

extern void (*NuCutSceneCharacterProcess)(int, instNUGCUTSCENE*, NuCutSceneRaw*, float, int);
__attribute__((visibility("hidden"))) void (**NuCutSceneCharacterProcessPtr)(int, instNUGCUTSCENE*,
                                                                             NuCutSceneRaw*, float, int)
    = &NuCutSceneCharacterProcess;

void NuSetCutSceneCharacterProcessFn(void (*fn)(int, instNUGCUTSCENE*, NuCutSceneRaw*, float, int)) {
    *NuCutSceneCharacterProcessPtr = fn;
}
