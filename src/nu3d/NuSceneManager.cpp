#include "nu3d/NuSceneManager.h"

void NuSceneManager::SetStoredHgobjMinMax(NuVector3Base& min, NuVector3Base& max) {
    m_StoredHgobjMin.x = min.x;
    m_StoredHgobjMin.y = min.y;
    m_StoredHgobjMin.z = min.z;
    m_StoredHgobjMax.x = max.x;
    m_StoredHgobjMax.y = max.y;
    m_StoredHgobjMax.z = max.z;
}
