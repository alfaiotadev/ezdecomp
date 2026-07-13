#pragma once

#include "legoapi/BoxGeom.h"

struct NuRenderBounds {
    char pad1[76];
    NuVector3Base min;  // 76
    char pad2[4];       // 88
    NuVector3Base max;  // 92
};

class NuRenderObject {
public:
    char pad[168];
    void* field_A8;
    NuRenderBounds* m_pBounds;  // 176
    float m_farClip;            // 184

    void GetBounds(NuVector3Base& min, NuVector3Base& max) const;
    void SetFarClip(float farClip);
};
