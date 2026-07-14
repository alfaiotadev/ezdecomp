#include "nu3d/NuRender.h"

void NuDrawBounds(const NuVector3Base&, const NuVector3Base&, NUMTX*, NUCOLOUR3 const&) {}

int g_CommandBuffer[2];

int NuRndrWasDrawnUnreflectedGobj() {
    return g_CommandBuffer[0];
}
