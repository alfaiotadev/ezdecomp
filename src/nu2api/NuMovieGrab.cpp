struct numoviegrabinfo_s {
    char initialised;
    char pad[3];
    int baseFrameNumber;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int outputWidth;
    int outputHeight;
};

__attribute__((visibility("hidden"))) numoviegrabinfo_s g_NuMovieGrabInfo;

void NuMovieGrabSetOutputResolution(int width, int height) {
    g_NuMovieGrabInfo.outputWidth = width;
    g_NuMovieGrabInfo.outputHeight = height;
}
