#include "nu3d/NuRender.h"

void NuDrawBounds(const NuVector3Base&, const NuVector3Base&, NUMTX*, NUCOLOUR3 const&) {}

int s_NuRndReflectionGobjFlag;
__attribute__((visibility("hidden"))) int* g_pNuRndReflectionGobj = &s_NuRndReflectionGobjFlag;

int NuRndIsReflectionGobj() {
    return *g_pNuRndReflectionGobj;
}
