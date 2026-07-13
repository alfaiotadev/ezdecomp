#pragma once

#include "legoapi/MechAIAvoidanceHelper.h"

class OrcaAgent {
public:
    void SetNewVelocity(const NuVec2& velocity);

private:
    char _0[24];
    NuVec2 m_newVelocity;
};
