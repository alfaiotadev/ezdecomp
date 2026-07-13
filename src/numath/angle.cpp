#include "numath/angle.h"

#include <algorithm>

constexpr float PI = 3.1415927f;

// todo Inlining of functions and improve readability
int NuAngAdd(int a, int b) {
    int sum = a + b;
    int temp = std::min(0x8000, sum);
    sum -= sum + ~temp + 0x10000 & 0xffff0000;
    temp = std::max(-0x7FFF, sum);
    sum += 0xFFFF - sum + temp & 0xffff0000;
    return sum;
}

int NuAngWrap(int angle) {
    int temp = std::min(0x8000, angle);
    angle -= angle + ~temp + 0x10000 & 0xffff0000;
    temp = std::max(-0x7FFF, angle);
    angle += 0xFFFF - angle + temp & 0xffff0000;
    return angle;
}
int NuAngSub(int a, int b) {
    int sum = a - b;
    int temp = std::min(0x8000, sum);
    sum -= sum + ~temp + 0x10000 & 0xffff0000;
    temp = std::max(-0x7FFF, sum);
    sum += 0xFFFF - sum + temp & 0xffff0000;
    return sum;
}
void NuAng2AltSol(int* out1, int* out2, int* out3, int a, int b, int c) {
    *out1 = a + 0x8000;
    *out2 = -0x8000 - b;
    *out3 = c + 0x8000;
}
float NuAngWrapRads(float angle) {
    while (angle > PI) {
        angle -= PI * 2;
    }
    while (-PI >= angle) {
        angle += PI * 2;
    }
    return angle;
}
float NuAngAddRads(float a, float b) {
    float sum = a + b;
    return NuAngWrapRads(sum);
}
float NuAngSubRads(float a, float b) {
    float difference = a - b;
    return NuAngWrapRads(difference);
}

void NuAngVecAddRads(NUVEC& out, NUVEC const& a, NUVEC const& b) {
    out.x = NuAngAddRads(a.x, b.x);
    out.y = NuAngAddRads(a.y, b.y);
    out.z = NuAngAddRads(a.z, b.z);
}
void NuAngVecSubRads(NUVEC& out, NUVEC const& a, NUVEC const& b) {
    out.x = NuAngSubRads(a.x, b.x);
    out.y = NuAngSubRads(a.y, b.y);
    out.z = NuAngSubRads(a.z, b.z);
}

float ApproxSin180(float x) {
    return (x - x * x) * 4.0f;
}
