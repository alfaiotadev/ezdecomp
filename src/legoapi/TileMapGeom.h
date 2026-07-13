#pragma once

#include "BoxGeom.h"

class TileMapGeom {
public:
    char pad[28];
    float m_28;
    float m_32;

    void GetLocalMinMax(NuVector3Base& min, NuVector3Base& max) const;
};
