#include "nu3d/NuRender.h"

void NuDrawBounds(const NuVector3Base&, const NuVector3Base&, NUMTX*, NUCOLOUR3 const&) {}

void NuRndrCurve(_vuv_s* p, int a, int b, float f0, float f1, const NuSmartPtr<NuMtl, true>& mtl,
                 unsigned int c, float f2, float f3) {
    NuRndrCurve2Clip(p, a, b, f0, f0, f1, mtl, c, f2, f3, 0.0f);
}
