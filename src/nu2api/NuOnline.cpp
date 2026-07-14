__attribute__((visibility("hidden"))) bool g_NuOnlineEnableAchievementUnlock;

void NuOnlineEnableAchievementUnlock(bool value) {
    g_NuOnlineEnableAchievementUnlock = value;
}
