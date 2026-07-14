#include "nu3d/NuOcclusionManager.h"

struct OcclusionManager {
    char pad[356];
    float occluderScreenSpaceThreshold;
};

extern OcclusionManager g_OcclusionManager;

void NuOcclusionManagerSetOccluderScreenSpaceThreshold(float threshold) {
    g_OcclusionManager.occluderScreenSpaceThreshold = threshold;
}
