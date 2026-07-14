#include "nucore/NuFile.h"

extern int g_NuFileSwapEndianOnWrite;

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

int NuFileSwapEndianOnWrite(int swap) {
    int old = g_NuFileSwapEndianOnWrite;
    g_NuFileSwapEndianOnWrite = swap;
    return old;
}
