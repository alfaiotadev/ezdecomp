#include "nu3d/NuViewport.h"

struct NuViewportGlobals {
    char pad[0xC];
    int hash;
};

__attribute__((visibility("hidden"))) NuViewportGlobals g_nuViewport;

void NuViewportClearHash() {
    g_nuViewport.hash = 0x811c9dc5;
}
