#include "nu3d/NuMaterialManager.h"

struct NuMaterialManagerContainer {
    char pad[0x10];
    NuMaterialManager* manager;
};

__attribute__((visibility("hidden"))) NuMaterialManagerContainer g_NuMaterialManager;

NuMaterialManager* NuMaterialManagerGet() {
    return g_NuMaterialManager.manager;
}
