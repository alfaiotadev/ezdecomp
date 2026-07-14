#include "nu3d/NuOcclusionManager.h"

extern OcclusionManager g_pOcclusionManager;

void NuOcclusionManagerSetOccluderDotProductThreshold(float threshold) {
    g_pOcclusionManager.m_occluderDotProductThreshold = threshold;
}
