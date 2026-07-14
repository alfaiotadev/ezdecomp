#include "nucore/NuFile.h"
#include "nucore/NuFileDevice.h"

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

NuFileDeviceType NuFileGetCurrentDeviceType() {
    return NuFileDevice::sm_DefaultDevice->m_type;
}
