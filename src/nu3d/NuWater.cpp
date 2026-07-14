struct NuWaterSettings {
    char pad[228];
    float speed;
};

__attribute__((visibility("hidden"))) NuWaterSettings* g_pNuWaterSettings;

void NuWaterSpeed(float speed) {
    g_pNuWaterSettings->speed = speed;
}
