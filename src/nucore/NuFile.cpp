#include "nucore/NuFile.h"

__attribute__((visibility("hidden"))) int* g_pNuFile_SwapEndianOnWrite;
__attribute__((visibility("hidden"))) int* g_pNuFile_SwapEndianOnRead;

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

int NuFileGetEndianSwapOnWrite() {
    return *g_pNuFile_SwapEndianOnWrite;
}
