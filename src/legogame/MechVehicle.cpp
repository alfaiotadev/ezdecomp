#include "legogame/MechVehicle.h"

struct NuMemoryManager {
    void BlockFree(void* ptr, unsigned int flags);
};

struct NuMemory {
    NuMemoryManager* GetThreadMem();
};

NuMemory* NuMemoryGet();

void MechVehicle::ClearVehicleAnimationContext() {
    void* pAnimationContext = m_animationContext;
    if (pAnimationContext != nullptr) {
        NuMemoryGet()->GetThreadMem()->BlockFree(pAnimationContext, 0);
        m_animationContext = nullptr;
    }
}
