#pragma once

#include "BoxGeom.h"

class SphereGeom {
public:
    char pad[28];
    float m_Radius;

    void GetLocalMinMax(NuVector3Base& min, NuVector3Base& max) const;
    void SupportPoint(const NuVector3Base& dir, NuVector3Base& out, int& index) const;
};
