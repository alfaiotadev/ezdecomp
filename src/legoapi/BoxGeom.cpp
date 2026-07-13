#include "BoxGeom.h"
#include "numath/types.h"

NuVector3Base LinearToNativeColourSpace(const NuVector3Base& v) {
    NuVector3Base r;
    r.x = v.x;
    r.y = v.y;
    r.z = v.z;
    return r;
}

NuVector3Base SRGBToNativeColourSpace(const NuVector3Base& v) {
    NuVector3Base r;
    float y = v.y;
    float x = v.x;
    float z = v.z;
    r.y = y * y;
    r.x = x * x;
    r.z = z * z;
    return r;
}

void BoxGeom::SetGhkExtents(const NuVector3Base& v) {
    float x = v.x;
    float y = v.y;
    float z = v.z;
    m_GhkExtents.x = x;
    m_GhkExtents.y = y;
    m_GhkExtents.z = z;
    m_GhkExtents.w = 0.0f;
}

void BoxGeom::GetLocalMinMax(NuVector3Base& min, NuVector3Base& max) const {
    int x = *(int*)&m_Extents.x;
    int y = *(int*)&m_Extents.y;
    int z = *(int*)&m_Extents.z;
    *(int*)&max.x = x;
    *(int*)&max.y = y;
    *(int*)&max.z = z;
    int minX = x ^ 0x80000000;
    int minY = y ^ 0x80000000;
    int minZ = z ^ 0x80000000;
    *(int*)&min.x = minX;
    *(int*)&min.y = minY;
    *(int*)&min.z = minZ;
}

void GetMinMaxBound(const NuVector3Base& a, const NuVector3Base& b, NUVEC& min, NUVEC& max) {
    float minX = a.x - b.x;
    float minY = a.y - b.y;
    float minZ = a.z - b.z;
    float maxX = a.x + b.x;
    float maxY = a.y + b.y;
    float maxZ = a.z + b.z;
    min.x = minX;
    min.y = minY;
    min.z = minZ;
    max.x = maxX;
    max.y = maxY;
    max.z = maxZ;
}
