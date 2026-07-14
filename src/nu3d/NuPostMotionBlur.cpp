#include "nu3d/NuPostMotionBlur.h"

__attribute__((visibility("hidden"))) float* g_pMotionBlurCharacterExposure;

float NuGetMotionBlurCharacterExposure() {
    return *g_pMotionBlurCharacterExposure;
}
