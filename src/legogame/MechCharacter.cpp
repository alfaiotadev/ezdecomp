#include "legoapi/BoxGeom.h"

class MechCharacter {
public:
    char pad[152];
    float x;
    float y;
    float z;

    NuVector3Base GetPosAsNuVec3() const;
};

NuVector3Base MechCharacter::GetPosAsNuVec3() const {
    NuVector3Base v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
