extern float g_cutsceneMotionBlurCharacterExposure;

void NuSetCutsceneMotionBlurCharacterExposure(float exposure) {
    g_cutsceneMotionBlurCharacterExposure = exposure < 0.0f ? 0.0f : exposure;
}
