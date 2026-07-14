extern float g_globalTexAnimTimeNoBlur;

float NuTexAnimGetGlobalClockNoBlur() {
    return g_globalTexAnimTimeNoBlur;
}

void NuTexAnimSetGlobalClockNoBlur(float value) {
    g_globalTexAnimTimeNoBlur = value;
}
