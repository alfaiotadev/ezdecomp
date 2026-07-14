struct NuMovieGrabInfo {
    char pad[0x14];
    int startFrameTemp;
    int startFrameCfg;
    int endFrameTemp;
    int endFrameCfg;
    float startTimeCfg;
    float endTimeCfg;
};

__attribute__((visibility("hidden"))) NuMovieGrabInfo g_nuMovieGrabInfo;

void NuMovieGrabSetEndFrame(int frame) {
    g_nuMovieGrabInfo.endFrameTemp = frame;
    g_nuMovieGrabInfo.endFrameCfg = frame;
}
