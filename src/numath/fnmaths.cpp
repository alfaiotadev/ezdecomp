#include "numath/fnmaths.h"

float fnMaths_lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float fnMaths_fmod(float a, float b) {
    return a - (float)((int)(a / b)) * b;
}
