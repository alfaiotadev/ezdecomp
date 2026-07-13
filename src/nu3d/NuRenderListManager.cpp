#include "nu3d/NuRenderListManager.h"

struct NuRenderListManagerSingleton {
    char pad[16];
    NuRenderListManager* pManager;
};

__attribute__((visibility("hidden"))) NuRenderListManagerSingleton g_NuRenderListManagerSingleton;

NuRenderListManager* NuRenderListManagerGet() {
    return g_NuRenderListManagerSingleton.pManager;
}
