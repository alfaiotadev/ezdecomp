#include "nu2api/NuTextureManager.h"

void NuTexWaitForLoad() {
    NuTextureManagerGet()->WaitForTextureLoad();
}
