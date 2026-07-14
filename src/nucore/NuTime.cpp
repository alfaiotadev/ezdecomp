struct NuApi {
    char pad[5692];
    float frameTime;
    char pad2[28];
    float forcedFrameTime;
    char pad3[12];
    int lockFrameTime;
    bool disableMaxFrameTimeClamping;
    char pad4[351];
};

__attribute__((visibility("hidden"))) NuApi* g_pNuApi;

void NuTimeLockFrameTime(int lock) {
    g_pNuApi->lockFrameTime = lock;
}
