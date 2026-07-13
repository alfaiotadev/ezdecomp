#include "CreatureIk.h"

void CreatureIk::SetLinearErp(float f) {
    m_linearErp = f;
}

void CreatureIk::SetLinearReductionFilter(const NuVector3Base& v) {
    m_linearReductionFilter.x = v.x;
    m_linearReductionFilter.y = v.y;
    m_linearReductionFilter.z = v.z;
}
