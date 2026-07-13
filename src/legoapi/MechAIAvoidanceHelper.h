#pragma once

struct NuVec2 {
    float x;
    float y;
};

class MechAIAvoidanceHelper {
public:
    static float PerpDot(const NuVec2& a, const NuVec2& b);
    static void Project2D(const NuVec2& a, const NuVec2& b, NuVec2& out);
    static void Project2DToAxis(const NuVec2& a, const NuVec2& axis, NuVec2& out);
    static float SignedAngle(const NuVec2& a, const NuVec2& b);
    static NuVec2 Rotate(const NuVec2& v, float angle);
};
