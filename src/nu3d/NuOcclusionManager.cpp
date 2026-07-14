#include "nu3d/NuOcclusionManager.h"

struct OcclusionManager {
    bool m_bInitialised;
};

__attribute__((visibility("hidden"))) OcclusionManager* g_pOcclusionManager;

bool NuOcclusionManagerIsInitialised() {
    return g_pOcclusionManager->m_bInitialised;
}
