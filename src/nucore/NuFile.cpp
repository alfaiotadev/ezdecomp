#include "nucore/NuFile.h"

class NuFileDevice {
public:
    char pad[0x50];
    char current_directory[256];
    static NuFileDevice* sm_DefaultDevice;
};

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

char* NuFileGetCurrentDirectory() {
    return NuFileDevice::sm_DefaultDevice->current_directory;
}
