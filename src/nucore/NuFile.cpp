#include "nucore/NuFile.h"

#include "nucore/NuString.h"

__attribute__((visibility("hidden"))) char** g_pCurrentDirectoryBase;

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

char* NuFileGetCurrentDirectory() {
    return *g_pCurrentDirectoryBase + 0x50;
}

void NuFileGetCurrentDirectory(char* dst) {
    NuStrCpy(dst, *g_pCurrentDirectoryBase + 0x50);
}
