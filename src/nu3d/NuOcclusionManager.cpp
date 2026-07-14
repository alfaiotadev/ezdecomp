#include "nu3d/OcclusionManager.h"

void NuOcclusionManagerSetEnabled(int enabled) {
    g_OcclusionManager.enabled = enabled != 0;
}
