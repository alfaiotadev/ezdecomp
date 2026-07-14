struct NuMovieGrabInfo {
    float field_0;
    int field_4;
    float field_8;
    char pad_12[8];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeTemp;
    float startTimeCfg;
    float endTimeTemp;
    float endTimeCfg;
};

__attribute__((visibility("hidden"))) NuMovieGrabInfo g_NuMovieGrabInfo;

void NuMovieGrabSetStartFrame(int frame) {
    g_NuMovieGrabInfo.startFrameTemp = frame;
    g_NuMovieGrabInfo.startFrameCfg = frame;
}
