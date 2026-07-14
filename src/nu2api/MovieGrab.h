#pragma once

struct NuMovieGrabConfig {
    char pad0[0x14];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
};

extern NuMovieGrabConfig g_NuMovieGrabConfig;

void NuMovieGrabSetEndFrameTemp(int endFrame);
