#include "nucore/NuMovieGrab.h"

struct numoviegrabinfo_s {
    char pad[0x14];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeTemp;
    float startTimeCfg;
    float endTimeTemp;
    float endTimeCfg;
};

__attribute__((visibility("hidden"))) numoviegrabinfo_s g_NuMovieGrabInfo;

float NuMovieGrabGetEndTimeCfg() {
    return g_NuMovieGrabInfo.endTimeCfg;
}
