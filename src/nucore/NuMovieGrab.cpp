#include "NuMovieGrab.h"

struct NuMovieGrabConfig {
    char pad0[20];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeTemp;
    float startTimeCfg;
    float endTimeTemp;
    float endTimeCfg;
};

__attribute__((visibility("hidden"))) NuMovieGrabConfig g_NuMovieGrabConfig;

void NuMovieGrabSetEndTime(float endTime) {
    g_NuMovieGrabConfig.endTimeTemp = endTime;
    g_NuMovieGrabConfig.endTimeCfg = endTime;
}
