#include "legoapi/RigidMass.h"

void RigidMass::ApplyForce(const NuVector3Base& v) {
    float t1 = field_84 + v.y;
    float t0 = field_80 + v.x;
    float t2 = field_88 + v.z;
    field_80 = t0;
    field_84 = t1;
    field_88 = t2;
}

void RigidMass::ApplyTorque(const NuVector3Base& v) {
    float t1 = field_100 + v.y;
    float t0 = field_96 + v.x;
    float t2 = field_104 + v.z;
    field_96 = t0;
    field_100 = t1;
    field_104 = t2;
}
