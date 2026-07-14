#include "nu3d/NuGCutScene.h"

struct NuGCutSceneGlobals {
    int dummy;
    volatile int baseFrameNumber;
};

static NuGCutSceneGlobals g_nuGCutSceneGlobals;

int NuGCutSceneGetBaseFrameNumber() {
    return g_nuGCutSceneGlobals.baseFrameNumber;
}
