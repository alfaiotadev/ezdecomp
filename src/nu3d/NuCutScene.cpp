enum CUTSCENESCALEMODE {};

extern "C" int cutscenecam_screenscale;

void NuGCutSetScaleMode(CUTSCENESCALEMODE mode) {
    cutscenecam_screenscale = mode;
}
