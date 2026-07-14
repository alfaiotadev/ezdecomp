#include "nu3d/NuPostMotionBlurFilter.h"

static float* volatile g_pCutsceneMotionBlurCameraExposure;

void NuSetCutsceneMotionBlurCameraExposure(float exposure) {
    *g_pCutsceneMotionBlurCameraExposure = exposure < 0.0f ? 0.0f : exposure;
}
