#include "nucore/NuFile.h"

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

__attribute__((disable_tail_calls)) unsigned int NuFileTimeToTimeStamp(NuSystemTime time) {
    return time.AsAndyDaviesTime();
}
