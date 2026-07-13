#pragma once

#include "legoapi/BoxGeom.h"

class CreatureIk {
public:
    char pad[88];
    float m_linearErp;
    char pad2[16];
    NuVector3Base m_linearReductionFilter;

    void SetLinearErp(float f);
    void SetLinearReductionFilter(const NuVector3Base& v);
};
