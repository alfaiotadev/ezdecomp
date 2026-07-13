#pragma once

#include "legoapi/BoxGeom.h"

class NuLightDescCommon {
public:
    NuVector3Base SRGBToLinear(const NuVector3Base& v) const;
};
