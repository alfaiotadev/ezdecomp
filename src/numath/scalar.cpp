#include "numath/scalar.h"
#include <math.h>

int TestNuMath() {
    return 1;
}

float NuFsign(float value) {
    return value >= 0.0f ? 1.0f : -1.0f;
}

__attribute__((visibility("hidden"))) float g_NuEquivTolerance;

void NuEquivTollerance(float tolerance) {
    g_NuEquivTolerance = tolerance;
}

float NuLog2(float value) {
    return logf(value) * 1.4426949f;
}

int NuPower2(int exponent) {
    int result = (exponent > 0x7f) ? 0x80 : 1;
    while (result < exponent) {
        result *= 2;
    }
    return result;
}

int NuMiscNextPow2(int value) {
    int i = 0;
    int result;
    do {
        result = 1 << i;
        i++;
    } while (result < value);
    return result;
}

float NuPow(float base, float exponent) {
    if (base == 0.0f) {
        return 0.0f;
    }
    return expf(logf(base) * exponent);
}
