#include "nucore/NuFile.h"

int NuFile_SwapEndianOnRead;

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

int NuFileSwapEndianOnRead(int value) {
    int old = NuFile_SwapEndianOnRead;
    NuFile_SwapEndianOnRead = value;
    return old;
}
