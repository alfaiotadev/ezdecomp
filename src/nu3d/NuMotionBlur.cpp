extern float g_cutsceneMotionBlurCameraExposure;
extern float g_cutsceneMotionBlurCharacterExposure;

void NuSetCutsceneMotionBlurCameraExposure(float value) {
    if (value < 0.0f) {
        value = 0.0f;
    }
    g_cutsceneMotionBlurCameraExposure = value;
}

void NuSetCutsceneMotionBlurCharacterExposure(float value) {
    if (value < 0.0f) {
        value = 0.0f;
    }
    g_cutsceneMotionBlurCharacterExposure = value;
}

float NuGetCutsceneMotionBlurCameraExposure() {
    return g_cutsceneMotionBlurCameraExposure;
}

float NuGetCutsceneMotionBlurCharacterExposure() {
    return g_cutsceneMotionBlurCharacterExposure;
}
