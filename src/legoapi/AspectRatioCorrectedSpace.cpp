#include "BoxGeom.h"

class AspectRatioCorrectedSpace {
public:
    NuVector3Base ConvertTo(const NuVector3Base& v) const;
    NuVector3Base ConvertFrom(const NuVector3Base& v) const;
    NuVector4Base ConvertTo(const NuVector4Base& v) const;
    NuVector4Base ConvertFrom(const NuVector4Base& v) const;

private:
    float scale;
};

NuVector3Base AspectRatioCorrectedSpace::ConvertTo(const NuVector3Base& v) const {
    NuVector3Base r;
    float x = v.x;
    r.y = v.y;
    r.z = v.z;
    r.x = x * scale;
    return r;
}

NuVector3Base AspectRatioCorrectedSpace::ConvertFrom(const NuVector3Base& v) const {
    NuVector3Base r;
    float x = v.x;
    r.y = v.y;
    r.z = v.z;
    r.x = x / scale;
    return r;
}

NuVector4Base AspectRatioCorrectedSpace::ConvertTo(const NuVector4Base& v) const {
    NuVector4Base r;
    float x = v.x;
    r.y = v.y;
    r.z = v.z;
    r.w = v.w;
    r.x = x * scale;
    return r;
}

NuVector4Base AspectRatioCorrectedSpace::ConvertFrom(const NuVector4Base& v) const {
    NuVector4Base r;
    float x = v.x;
    r.y = v.y;
    r.z = v.z;
    r.w = v.w;
    r.x = x / scale;
    return r;
}
