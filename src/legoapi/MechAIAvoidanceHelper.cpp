#include "legoapi/MechAIAvoidanceHelper.h"
#include "numath/scalar.h"

float MechAIAvoidanceHelper::PerpDot(const NuVec2& a, const NuVec2& b) {
    return a.x * b.y - a.y * b.x;
}

void MechAIAvoidanceHelper::Project2D(const NuVec2& a, const NuVec2& b, NuVec2& out) {
    float t = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
    NuVec2 result;
    result.x = b.x * t;
    result.y = b.y * t;
    out = result;
}

void MechAIAvoidanceHelper::Project2DToAxis(const NuVec2& a, const NuVec2& axis, NuVec2& out) {
    float t = a.x * axis.x + a.y * axis.y;
    NuVec2 result;
    result.x = axis.x * t;
    result.y = axis.y * t;
    out = result;
}

float MechAIAvoidanceHelper::SignedAngle(const NuVec2& a, const NuVec2& b) {
    float cross = a.x * b.y - a.y * b.x;
    float dot = a.x * b.x + a.y * b.y;
    return NuATan2f(cross, dot);
}

NuVec2 MechAIAvoidanceHelper::Rotate(const NuVec2& v, float angle) {
    float c = NuCosf(angle);
    float s = NuSinf(angle);
    NuVec2 result;
    result.x = c * v.x + s * v.y;
    result.y = -(s * v.x) + c * v.y;
    return result;
}
