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

__attribute__((visibility("hidden"))) numoviegrabinfo_s g_NuMovieGrabInfo;

void NuMovieGrabSetStartTimeTemp(float f) {
    g_NuMovieGrabInfo.startTimeTemp = f;
}
