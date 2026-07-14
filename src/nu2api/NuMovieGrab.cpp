#include "nu2api/NuMovieGrab.h"

__attribute__((visibility("hidden"))) numoviegrabinfo_s g_NuMovieGrabConfig;

float NuMovieGrabGetStartFrameTemp() {
    return (float)g_NuMovieGrabConfig.startFrameTemp;
}
