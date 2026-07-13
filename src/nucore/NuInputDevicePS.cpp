#include "cstring"
#include "nn/hid.h"
#include "nucore/NuInputDevicePS.h"

static float deadZone = 0.2f;

int NuInputDevicePS::GetNumPorts() {
    return 9;
}
void NuInputDevicePS::ClassShutdownPS() {}
bool NuInputDevicePS::IsConnectedPS(unsigned int port) {
    if (port > 8) {
        return false;
    }
    const u32& currentNpadId = m_npadIDs[port];
    nn::hid::NpadStyleSet currentStyle = nn::hid::GetNpadStyleSet(currentNpadId);
    return currentStyle.IsAnyOn();
}
bool NuInputDevicePS::IsInterceptedPS(unsigned int port) {
    return false;
}
int NuInputDevicePS::GetAttachmentTypePS(unsigned int port) {
    return 0;
}
int NuInputDevicePS::GetCapsPS(unsigned int port) {
    if (port < GetNumPorts()) {
        return 184;
    }
    return 24;
}
float NuInputDevicePS::GetStickDeadZone(unsigned int port) {
    return deadZone;
}
float NuInputDevicePS::GetButtonDeadZone(unsigned int port) {
    return deadZone;
}
void NuInputDevicePS::ReadTouchDataPS(unsigned int port, NuInputTouchData* touchData) {
    memset(touchData, 0, sizeof(NuInputTouchData));
}
void NuInputDevicePS::ReadMouseDataPS(unsigned int port, NuInputMouseData* mouseData) {
    memset(mouseData, 0, sizeof(NuInputMouseData));
}
unsigned int NuInputDevicePS::EnableDPDPS(unsigned int port) {
    return port;
}
unsigned int NuInputDevicePS::DisableDPDPS(unsigned int port) {
    return port;
}
bool NuInputDevicePS::HasHeadphonesConnectedPS(unsigned int port) {
    return false;
}
float NuInputDevicePS::GetVolumePS(unsigned int port) {
    return 0.0f;
}
