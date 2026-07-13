#include "nu3d/NuRenderObject.h"

void NuRenderObject::GetBounds(NuVector3Base& min, NuVector3Base& max) const {
    const NuRenderBounds* bounds = m_pBounds;
    float minX = bounds->min.x;
    float minY = bounds->min.y;
    float minZ = bounds->min.z;
    min.x = minX;
    min.y = minY;
    min.z = minZ;
    float maxX = bounds->max.x;
    float maxY = bounds->max.y;
    float maxZ = bounds->max.z;
    max.x = maxX;
    max.y = maxY;
    max.z = maxZ;
}

void NuRenderObject::SetFarClip(float farClip) {
    m_farClip = farClip;
}
