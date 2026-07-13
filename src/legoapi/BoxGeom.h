#pragma once

struct NuVector3Base {
    float x, y, z;
    ~NuVector3Base() {}
};

struct NuVector4Base {
    float x, y, z, w;
    ~NuVector4Base() {}
};

NuVector3Base LinearToNativeColourSpace(const NuVector3Base& v);
NuVector3Base SRGBToNativeColourSpace(const NuVector3Base& v);

struct NUVEC;
void GetMinMaxBound(const NuVector3Base& a, const NuVector3Base& b, NUVEC& min, NUVEC& max);

class BoxGeom {
public:
    char pad[28];
    NuVector4Base m_GhkExtents;
    char pad2[4];
    NuVector3Base m_Extents;

    void SetGhkExtents(const NuVector3Base& v);
    void GetLocalMinMax(NuVector3Base& min, NuVector3Base& max) const;
};
