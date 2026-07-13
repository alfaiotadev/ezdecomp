#include "legoapi/BoxGeom.h"
#include <cstring>

class Character {
public:
    char pad[144];
    float footX;
    float footY;
    float footZ;
    char pad2[160];
    float field316;
    char pad3[16];
    float field336;

    void GetFootPos(NuVector3Base& pos);
};

void Character::GetFootPos(NuVector3Base& pos) {
    pos.z = footZ;
    std::memcpy(&pos, &footX, 8);
    pos.y = field336 + field316;
}
