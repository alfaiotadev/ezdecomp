#ifndef NU3D_NUMOVIEGRAB_H
#define NU3D_NUMOVIEGRAB_H

struct numoviegrabinfo_s {
    char pad[20];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeTemp;
    float startTimeCfg;
    float endTimeTemp;
    float endTimeCfg;
};

float NuMovieGrabGetStartTimeCfg();

#endif
