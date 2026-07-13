#include "legoapi/NuKDOPBase.h"

NuVector3Base NuKDOPBase::ClosestPointOnPlaneToOrigin(const NuVector4Base& plane) {
    float y2 = plane.y * plane.y;
    float z = plane.z;
    float w = plane.w;
    float yw = plane.y * w;
    float x2 = plane.x * plane.x;
    float xw = plane.x * w;
    float zw = z * w;
    float z2 = z * z;
    float dot = x2 + y2;
    dot = dot + z2;
    NuVector3Base result;
    result.x = xw / dot;
    result.y = yw / dot;
    result.z = zw / dot;
    return result;
}

NuVector3Base NuKDOPBase::ClosestPointOnPlane(const NuVector4Base& plane, const NuVector3Base& point) {
    float dist = (plane.x * point.x + plane.y * point.y + plane.z * point.z) - plane.w;
    float rx = point.x - plane.x * dist;
    float ry = point.y - plane.y * dist;
    float rz = point.z - plane.z * dist;
    NuVector3Base result;
    result.x = rx;
    result.y = ry;
    result.z = rz;
    return result;
}
