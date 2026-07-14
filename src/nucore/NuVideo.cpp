#include "NuVideo.h"
#include "NuVideoState.h"

void NuVideoSetBrightnessPS() {}

int NuVideoGetAspectPS() {
    return 1;
}

void NuVideoSetResolution(int width, int height) {
    nuvideo_settings->width = width;
    nuvideo_settings->height = height;
}
