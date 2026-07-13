#include "legoapi/BoxGeom.h"

class DynoScene {
public:
    char pad[0x14];
    NuVector3Base gravity;

    void SetGravity(const NuVector3Base& v);
};

void DynoScene::SetGravity(const NuVector3Base& v) {
    gravity.x = v.x;
    gravity.y = v.y;
    gravity.z = v.z;
}
