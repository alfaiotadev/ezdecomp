#pragma once

#include "legoapi/BoxGeom.h"

struct Inertia {
    char pad[80];
    NuVector3Base centreOfMass;

    void GetCentreOfMass(NuVector3Base& out);
};
