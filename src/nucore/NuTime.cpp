#include "nucore/NuTime.h"

NuTimeData nuapi;

float NuTimeGetFrameTime() {
    return nuapi.frameTime;
}

void NuTimeForceFrameTime(float) {
}

void NuTimeLockFrameTime(int) {
}

void NuTimeDisableMaxFrameTimeClamping(bool) {
}
