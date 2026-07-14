struct NuMovieGrabConfig {
    char pad0[20];
    int startFrameTemp;
    int startFrame;
    int endFrameTemp;
    int endFrame;
    float startTimeTemp;
    float startTime;
    float endTimeTemp;
    float endTime;
};

__attribute__((visibility("hidden"))) NuMovieGrabConfig g_NuMovieGrabConfig;

void NuMovieGrabSetStartTime(float startTime) {
    g_NuMovieGrabConfig.startTimeTemp = startTime;
    g_NuMovieGrabConfig.startTime = startTime;
}
