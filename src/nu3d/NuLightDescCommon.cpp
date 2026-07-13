#include "nu3d/NuLightDescCommon.h"

NuVector3Base NuLightDescCommon::SRGBToLinear(const NuVector3Base& v) const {
    float x = v.x;
    float y = v.y;
    float z = v.z;
    NuVector3Base result;
    result.y = y * y;
    result.x = x * x;
    result.z = z * z;
    return result;
}
