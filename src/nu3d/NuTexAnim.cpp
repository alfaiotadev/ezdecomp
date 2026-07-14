#include "nu3d/NuTexAnim.h"

__attribute__((visibility("hidden"))) float* g_NuTexAnimGlobalClock;

float NuTexAnimGetGlobalClock() {
    return *g_NuTexAnimGlobalClock;
}
