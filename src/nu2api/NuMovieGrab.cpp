#include "nu2api/NuMovieGrab.h"

__attribute__((visibility("hidden"))) numoviegrabconfig_s g_NuMovieGrabConfig;

void NuMovieGrabSetStartFrameTemp(int startFrame) {
    g_NuMovieGrabConfig.startFrameTemp = startFrame;
}
