#include "nu2api/MovieGrab.h"

__attribute__((visibility("hidden"))) NuMovieGrabConfig g_NuMovieGrabConfig;

void NuMovieGrabSetEndFrameTemp(int endFrame) {
    g_NuMovieGrabConfig.endFrameTemp = endFrame;
}
