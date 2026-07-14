#pragma once

struct NuTimeData {
    char _pad0[5692];
    float frameTime;
    float forcedFrameTime;
    char _pad1[12];
    int frameTimeLocked;
    bool disableMaxFrameTimeClamping;
};

extern NuTimeData nuapi;

float NuTimeGetFrameTime();
void NuTimeForceFrameTime(float);
void NuTimeLockFrameTime(int);
void NuTimeDisableMaxFrameTimeClamping(bool);
