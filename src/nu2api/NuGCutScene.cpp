struct MemoryManager;

struct NuGCutSceneSysData {
    MemoryManager* memoryManager;
};

__attribute__((visibility("hidden"))) NuGCutSceneSysData* g_pNuGCutSceneSysData;

void NuGCutSceneSysInitMemoryManager(MemoryManager* mgr) {
    g_pNuGCutSceneSysData->memoryManager = mgr;
}
