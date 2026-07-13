#pragma once

#include "legoapi/BoxGeom.h"

class NuSceneManager {
public:
    char pad[0x100];
    NuVector3Base m_StoredHgobjMin;
    char pad_0x10c[4];
    NuVector3Base m_StoredHgobjMax;

    void SetStoredHgobjMinMax(NuVector3Base& min, NuVector3Base& max);
};
