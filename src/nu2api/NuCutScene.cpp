#include "nu2api/NuCutScene.h"

struct NuCutSceneVFXFixUpState {
    long (*fn)(const char*, NuCutSceneRaw*, void*);
};

__attribute__((visibility("hidden"))) NuCutSceneVFXFixUpState* gNuCutSceneVFXFixUpState;

void NuSetCutSceneVFXFixUpFn(long (*fn)(const char*, NuCutSceneRaw*, void*)) {
    gNuCutSceneVFXFixUpState->fn = fn;
}
