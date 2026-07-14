struct NuTime {
    char pad[0x1670];
    bool disableMaxFrameTimeClamping;
};

extern NuTime g_NuTime;

void NuTimeDisableMaxFrameTimeClamping(bool flag) {
    g_NuTime.disableMaxFrameTimeClamping = flag;
}
