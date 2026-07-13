#include "SphereGeom.h"

void SphereGeom::GetLocalMinMax(NuVector3Base& min, NuVector3Base& max) const {
    int r = *(int*)&m_Radius;
    int nr = r ^ 0x80000000;
    *(int*)&min.x = nr;
    *(int*)&min.y = nr;
    *(int*)&min.z = nr;
    *(int*)&max.x = r;
    *(int*)&max.y = r;
    *(int*)&max.z = r;
}

void SphereGeom::SupportPoint(const NuVector3Base& dir, NuVector3Base& out, int& index) const {
    out.x = 0.0f;
    out.y = 0.0f;
    out.z = 0.0f;
}
