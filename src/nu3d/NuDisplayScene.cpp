#include "nu3d/NuDisplayScene.h"

void NuDisplayScene::GetClipObjectLocalExtents(unsigned int, NuVector3Base& a, NuVector3Base& b) const {
    a.x = 0.0f;
    a.y = 0.0f;
    a.z = 0.0f;
    b.x = 0.0f;
    b.y = 0.0f;
    b.z = 0.0f;
}
