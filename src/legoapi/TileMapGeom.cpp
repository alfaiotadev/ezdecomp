#include "TileMapGeom.h"

void TileMapGeom::GetLocalMinMax(NuVector3Base& min, NuVector3Base& max) const {
    float f0 = m_28;
    float f1 = m_32;
    *(int*)&min.y = 0xff7fffff;
    min.z = -f1;
    min.x = -f0;
    int i0 = *(int*)&m_28;
    int i1 = *(int*)&m_32;
    *(int*)&max.x = i0;
    *(int*)&max.y = 0x7f7fffff;
    *(int*)&max.z = i1;
}
