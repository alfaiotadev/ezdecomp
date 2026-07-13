#include "numath/random.h"

#include <cmath>

using namespace std;

void NuRandSeed(unsigned int seed) {
    fseed = seed;
}
unsigned int NuRandGetSeed() {
    return fseed;
}
void NuRandNextSeed(unsigned int* seed) {
    *seed = *seed * 0x19660d + 0x3c6ef35f;
}
float NuRandFloatSeeded(unsigned int* seed) {
    NuRandNextSeed(seed);
    union {
        unsigned int i;
        float f;
    } converter{};
    converter.i = (*seed & 0x7fffff) | 0x3f800000;
    return converter.f - 1.0f;
}

float NuRandFloat() {
    return NuRandFloatSeeded(&fseed);
}
float NuRandFloatInRange(float min, float max) {
    float range = max - min;
    float random = NuRandFloatSeeded(&fseed);
    return min + range * random;
}
unsigned int NuRandIntSeeded(unsigned int* seed) {
    NuRandNextSeed(seed);
    return *seed;
}
unsigned int NuRandInt() {
    NuRandNextSeed(&fseed);
    return fseed;
}
// todo check again
int NuRandIntInRange(unsigned int min, unsigned int max) {
    unsigned int* seedPtr = &fseed;
    float range = static_cast<float>((1 - min) + max);
    unsigned int seed = *seedPtr;
    seed = seed * 0x19660d + 0x3c6ef35f;

    *seedPtr = seed;
    union {
        unsigned int i;
        float f;
    } converter;
    converter.i = (seed & 0x7fffff) | 0x3f800000;
    return static_cast<unsigned int>(range * (converter.f - 1.0f)) + min;
}
// todo check again
int NuRandInt(unsigned int min, unsigned int max) {
    float range = static_cast<float>(max - min);

    NuRandNextSeed(&fseed);

    union {
        unsigned int i;
        float f;
    } converter;
    converter.i = (fseed & 0x7fffff) | 0x3f800000;

    float randValue = range * (converter.f - 1.0f);

    float temp1 = randValue + 0.5f;
    int val1 = static_cast<int>(temp1);
    float fval1 = static_cast<float>(val1);

    float temp2 = randValue - 0.5f;
    int val2 = static_cast<int>(temp2);
    float fval2 = static_cast<float>(val2);
    float diff2 = temp2 - fval2;
    float adjusted2 = fval2 - 1.0f;
    fval2 = diff2 >= 0.0f ? fval2 : adjusted2;

    float incremented = fval2 + 1.0f;
    fval2 = fval2 == temp2 ? fval2 : incremented;

    float result = randValue >= 0.0f ? fval1 : fval2;

    return static_cast<unsigned int>(result) + min;
}
void NuRandSetSeed(nunrand_s* state, int newSeed) {
    nunrand_s* targetState = state;
    if (targetState == nullptr) {
        targetState = &g_defaultNuRandState;
    }
    targetState->seed = newSeed;
}
unsigned int NuRand(nunrand_s* state) {
    nunrand_s* targetState;
    unsigned int currentSeed;

    if (state == nullptr) {
        targetState = &g_defaultNuRandState;
        currentSeed = targetState->seed;
    } else {
        targetState = state;
        currentSeed = targetState->seed;
        if (currentSeed == 0) {
            currentSeed = 1;
            targetState->seed = 1;
        }
    }

    unsigned int transformedSeed = currentSeed ^ 0x75BD924;

    int quotient = static_cast<int>(transformedSeed) / 0x1F31D;
    unsigned int remainder = quotient * 0xFFFE0CE3u + transformedSeed;

    unsigned int component1 = remainder * 0x41A7;
    int component2 = quotient * static_cast<int>(0xFFFFF4EC);
    unsigned int nextState = component1 + component2;

    unsigned int normalizedState;
    if (static_cast<int>(nextState) < 0) {
        normalizedState = nextState + 0x7FFFFFFF;
    } else {
        normalizedState = nextState;
    }

    unsigned int result = normalizedState ^ 0x75BD924;
    targetState->seed = result;
    return result;
}

float NuFloatRand(nunrand_s* state) {
    nunrand_s* targetState;
    unsigned int currentSeed;
    static const float scale = 4.6566126e-10f;

    if (state == nullptr) {
        targetState = &g_defaultNuRandState;
        currentSeed = targetState->seed;
    } else {
        targetState = state;
        currentSeed = targetState->seed;
        if (currentSeed == 0) {
            currentSeed = 1;
            targetState->seed = 1;
        }
    }

    unsigned int transformedSeed = currentSeed ^ 0x75BD924;

    int quotient = static_cast<int>(transformedSeed) / 0x1F31D;
    unsigned int remainder = quotient * 0xFFFE0CE3u + transformedSeed;

    unsigned int component1 = remainder * 0x41A7;
    int component2 = quotient * static_cast<int>(0xFFFFF4EC);
    unsigned int nextState = component1 + component2;

    unsigned int normalizedState;
    if (static_cast<int>(nextState) < 0) {
        normalizedState = nextState + 0x7FFFFFFF;
    } else {
        normalizedState = nextState;
    }

    unsigned int result = normalizedState ^ 0x75BD924;
    targetState->seed = result;

    return static_cast<float>(static_cast<int>(result)) * scale;
}
