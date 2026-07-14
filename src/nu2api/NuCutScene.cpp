#include "nu2api/NuCutScene.h"

struct CutSceneCharacterDestroyDataCallbacks {
    void (*fn)(NuCutSceneRaw*, NuANI4AnimRaw*, NuCutSceneRawCharExtra*, instNUGCUTCHAR_s*);
};

__attribute__((visibility("hidden")))
CutSceneCharacterDestroyDataCallbacks* g_pCutSceneCharacterDestroyDataCallbacks;

__attribute__((used)) void NuSetCutSceneCharacterDestroyDataFn(void (*fn)(NuCutSceneRaw*, NuANI4AnimRaw*,
                                                                          NuCutSceneRawCharExtra*,
                                                                          instNUGCUTCHAR_s*)) {
    g_pCutSceneCharacterDestroyDataCallbacks->fn = fn;
}
