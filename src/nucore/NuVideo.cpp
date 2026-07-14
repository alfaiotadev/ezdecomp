#include "NuVideo.h"

int NuRenderThreadSetup::UserDisplay = 0;

void NuVideoSetBrightnessPS() {}

int NuVideoGetAspectPS() {
    return 1;
}

void NuVideoSetDisplayType(NUVIDEO_DISPLAY_TYPE type) {
    NuRenderThreadSetup::UserDisplay = type;
}
