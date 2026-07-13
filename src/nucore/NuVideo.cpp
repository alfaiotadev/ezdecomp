#include "NuVideo.h"

struct NuApi {
    char pad[0x150c];
    int m_videoSwapMode;
};

NuApi nuapi;

void NuVideoSetBrightnessPS() {}

int NuVideoGetAspectPS() {
    return 1;
}

int NuVideoGetSwapMode() {
    return nuapi.m_videoSwapMode;
}
