__attribute__((visibility("hidden"))) char** g_NuCrashDumpRoot;

char* NuCrashDumpGetRoot() {
    return *g_NuCrashDumpRoot;
}
