#include "nu3d/NuMovieGrab.h"

__attribute__((visibility("hidden"))) numoviegrabinfo_s g_NuMovieGrabInfo;

float NuMovieGrabGetStartTimeCfg() {
    return g_NuMovieGrabInfo.startTimeCfg;
}
