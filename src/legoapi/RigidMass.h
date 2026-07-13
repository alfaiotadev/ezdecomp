#pragma once

#include "legoapi/BoxGeom.h"

class RigidMass {
public:
    char pad[80];
    float field_80;
    float field_84;
    float field_88;
    char pad2[4];
    float field_96;
    float field_100;
    float field_104;

    void ApplyForce(const NuVector3Base& v);
    void ApplyTorque(const NuVector3Base& v);
};
