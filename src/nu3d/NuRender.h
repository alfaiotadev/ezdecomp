#pragma once

#include "legoapi/BoxGeom.h"
#include "numath/types.h"

struct NUCOLOUR3 {
    float r;
    float g;
    float b;
};

void NuRndrSetParticleRotation(NUMTX* rotation);
void NuDrawBounds(const NuVector3Base& min, const NuVector3Base& max, NUMTX* mtx, NUCOLOUR3 const& colour);
