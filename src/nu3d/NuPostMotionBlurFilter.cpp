#include "nu3d/NuPostMotionBlurFilter.h"

__attribute__((visibility("hidden"))) float* g_pNuMotionBlurCameraExposure;

void NuSetMotionBlurCameraExposure(float exposure) {
    exposure = exposure < 0.0f ? 0.0f : exposure;
    *g_pNuMotionBlurCameraExposure = exposure;
}
