#pragma once

#include "legoapi/BoxGeom.h"
#include "numath/types.h"

struct NUCOLOUR3 {
    float r;
    float g;
    float b;
};

struct _vuv_s;
class NuMtl;
template <class T, bool b>
class NuSmartPtr;

void NuDrawBounds(const NuVector3Base& min, const NuVector3Base& max, NUMTX* mtx, NUCOLOUR3 const& colour);
void NuRndrCurve2Clip(_vuv_s*, int, int, float, float, float, const NuSmartPtr<NuMtl, true>&, unsigned int,
                      float, float, float);
void NuRndrCurve(_vuv_s*, int, int, float, float, const NuSmartPtr<NuMtl, true>&, unsigned int, float, float);
