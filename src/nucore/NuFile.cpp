#include "nucore/NuFile.h"

__attribute__((visibility("hidden"))) int* this_platformClass;

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

int NuGetCurrPlatformClass() {
    return *this_platformClass;
}
