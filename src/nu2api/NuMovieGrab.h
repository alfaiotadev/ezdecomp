#ifndef NU2API_NU_MOVIE_GRAB_H
#define NU2API_NU_MOVIE_GRAB_H

struct numoviegrabconfig_s {
    float field_0;
    int field_4;
    float field_8;
    int field_C;
    int field_10;
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeTemp;
    float startTimeCfg;
    float endTimeTemp;
    float endTimeCfg;
};

__attribute__((visibility("hidden"))) extern numoviegrabconfig_s g_NuMovieGrabConfig;

void NuMovieGrabSetStartFrameTemp(int startFrame);

#endif
