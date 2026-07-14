#include "nu3d/NuMovieGrab.h"

struct NuMovieGrabInfo {
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

__attribute__((visibility("hidden"))) NuMovieGrabInfo g_NuMovieGrabInfo;

int NuMovieGrabGetEndFrameCfg(void) {
    return g_NuMovieGrabInfo.endFrameCfg;
}
