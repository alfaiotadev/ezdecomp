#include <cstddef>

class VfxThing;

__attribute__((visibility("hidden"))) __attribute__((aligned(4096))) VfxThing* gNuGCutSceneSysVfxThing;

struct NuGCutSceneSysBackgroundData {
    char pad[0x10];
    void* load;
    char pad2[0x68];
};

__attribute__((visibility("hidden")))
__attribute__((aligned(0x80))) NuGCutSceneSysBackgroundData gNuGCutSceneSysBackgroundData;

void NuGCutSceneSysBackgroundFlush() {
    gNuGCutSceneSysBackgroundData.load = nullptr;
}
