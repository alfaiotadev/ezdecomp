#include "NuVideo.h"

extern "C" float nuapi[1524];

void NuVideoSetBrightnessPS() {}

int NuVideoGetAspectPS() {
    return 1;
}

int NuVideoGetNativeFPS() {
    return (int)nuapi[1350];
}
