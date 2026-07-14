#include "nucore/NuGCutScene.h"

extern float TGAFrameStep __asm__("TGAFrameStep");

void NuGCutSceneSetTGAFrameStep(float step) {
    TGAFrameStep = step;
}
