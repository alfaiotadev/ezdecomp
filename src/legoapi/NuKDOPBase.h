#pragma once

#include "legoapi/BoxGeom.h"

class NuKDOPBase {
public:
    static NuVector3Base ClosestPointOnPlaneToOrigin(const NuVector4Base& plane);
    static NuVector3Base ClosestPointOnPlane(const NuVector4Base& plane, const NuVector3Base& point);
};
