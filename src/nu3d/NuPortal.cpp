struct NuPortalInfo {
    int enabled;
};

extern NuPortalInfo g_NuPortalInfo;

int NuPortalIsEnabled(void) {
    return g_NuPortalInfo.enabled;
}
