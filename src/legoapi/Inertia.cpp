#include "legoapi/Inertia.h"

void Inertia::GetCentreOfMass(NuVector3Base& out) {
    float x = centreOfMass.x;
    float y = centreOfMass.y;
    float z = centreOfMass.z;
    out.x = x;
    out.y = y;
    out.z = z;
}
