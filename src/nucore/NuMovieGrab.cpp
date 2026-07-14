#include "nucore/NuMovieGrab.h"

struct numoviegrabinfo_s {
    char pad[20];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeTemp;
    float startTime;
    float endTimeTemp;
    float endTime;
};

__attribute__((visibility("hidden"))) numoviegrabinfo_s g_movieGrabInfo;

void NuMovieGrabSetEndTimeTemp(float value) {
    g_movieGrabInfo.endTimeTemp = value;
}
