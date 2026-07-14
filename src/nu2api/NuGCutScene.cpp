#include "nu2api/NuGCutScene.h"

extern "C" float LastOutputtedFrameTime;

float NuGCutSceneGetLastOutPuttedFrameTime() {
    return LastOutputtedFrameTime;
}
