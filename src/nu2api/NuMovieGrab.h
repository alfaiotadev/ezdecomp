#ifndef NU2API_NUMOVIEGRAB_H
#define NU2API_NUMOVIEGRAB_H

struct numoviegrabinfo_s {
    char pad[20];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
};

float NuMovieGrabGetStartFrameTemp();

#endif  // NU2API_NUMOVIEGRAB_H
