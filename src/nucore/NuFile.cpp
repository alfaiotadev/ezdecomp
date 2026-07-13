#include "nucore/NuFile.h"

int NuFile_SwapEndianOnWrite;
int NuFile_SwapEndianOnRead;

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

int NuFileSwapEndianOnWrite(int value) {
    int old = NuFile_SwapEndianOnWrite;
    NuFile_SwapEndianOnWrite = value;
    return old;
}

int NuFileSwapEndianOnRead(int value) {
    int old = NuFile_SwapEndianOnRead;
    NuFile_SwapEndianOnRead = value;
    return old;
}

int NuFileGetEndianSwapOnRead() {
    return NuFile_SwapEndianOnRead;
}

int NuFileGetEndianSwapOnWrite() {
    return NuFile_SwapEndianOnWrite;
}
