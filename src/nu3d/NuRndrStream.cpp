__attribute__((visibility("hidden"))) int* g_lastUsed;

int NuRndrStreamGetLastUsed(void) {
    return *g_lastUsed;
}
