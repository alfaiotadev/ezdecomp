#include "nu2api/MovieGrab.h"

struct MovieGrabConfig {
    char pad[20];
    int startFrameTemp;
    volatile int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeTemp;
    float startTime;
    float endTimeTemp;
    float endTime;
    float startTimeCfg;
    float endTimeCfg;
};

static MovieGrabConfig g_movieGrabConfig;

int NuMovieGrabGetStartFrameCfg() {
    return g_movieGrabConfig.startFrameCfg;
}
