#include "cmath"
#include "nucore/NuInputDevice.h"
#include "nucore/NuInputDevicePS.h"

NuInputDevice::~NuInputDevice() = default;

int NuInputDevice::GetCaps() const {
    return m_Caps;
}
void NuInputDevice::KillRumble() {
    m_RumbleKilled = true;
    m_HighFreqMotor = 0.0f;
    m_LowFreqMotor = 0.0f;
}
int NuInputDevice::GetType() const {
    return m_Type;
}

void NuInputDevice::SetDisconnected() {
    m_IsConnected = false;
    m_IsIntercepted = false;
    m_Type = 0;
    m_Caps = 0;
    m_LowFreqMotor = 0.0f;
    m_HighFreqMotor = 0.0f;
    m_Volume = 0;
    m_HasHeadphones = false;
    m_RumbleDuration = 0.0f;
    m_RumbleIdleTimer = 0.0f;
}

void NuInputDevice::DeadZone(NUPADANALOGVALUE axis, float deadZone) {
    float* pValue = &m_AnalogValues[axis];
    float val = *pValue;

    if (val > deadZone) {
        val -= deadZone;
    } else {
        if (val < -deadZone) {
            val += deadZone;
        } else {
            *pValue = 0.0f;
            return;
        }
    }

    *pValue = val / (1.0f - deadZone);
}
unsigned int NuInputDevice::GetPort() const {
    return m_Port;
}
unsigned int NuInputDevice::GetIdentifier_CAFE_SPECIFIC() const {
    return m_CafeSpecificId;
}
int NuInputDevice::GetLastValidType() const {
    return m_LastValidType;
}
int NuInputDevice::GetAttachmentType() const {
    return m_AttachmentType;
}
bool NuInputDevice::SupportsCaps(unsigned int cap) const {
    return (m_Caps & cap) != 0;
}
bool NuInputDevice::IsConnected() const {
    return m_IsConnected;
}
bool NuInputDevice::IsIntercepted() const {
    return m_IsIntercepted;
}
// todo find correct implementation, currently using a matching hack
bool NuInputDevice::IsButtonPressed(unsigned int button) const {
    if (m_IsConnected == 0)
        goto ret_false;
    if ((m_Buttons & button) == 0)
        goto ret_false;
    return true;
ret_false:
    return false;
}
unsigned int NuInputDevice::GetButtons() const {
    if (m_IsConnected) {
        return m_Buttons;
    }
    return 0;
}
float NuInputDevice::GetAnalogValue(NUPADANALOGVALUE index) const {
    if (m_IsConnected) {
        return m_AnalogValues[index];
    }
    return 0.0f;
}
float NuInputDevice::GetMotionValue(NUPADMOTIONVALUE index) const {
    if (m_IsConnected) {
        return m_MotionValues[index];
    }
    return 0.0f;
}
const NuInputTouchData* NuInputDevice::GetTouchData() const {
    return &m_TouchData;
}
const NuInputMouseData* NuInputDevice::GetMouseData() const {
    return &m_MouseData;
}
void NuInputDevice::SetMotors(float lowFreq, float highFreq) {
    m_LowFreqMotor = fminf(fmaxf(lowFreq, 0.0f), 1.0f);
    m_HighFreqMotor = fminf(fmaxf(highFreq, 0.0f), 1.0f);
}
void NuInputDevice::EnableDPD() {
    NuInputDevicePS::EnableDPDPS(m_Port);
}
void NuInputDevice::DisableDPD() {
    NuInputDevicePS::DisableDPDPS(m_Port);
}
bool NuInputDevice::HasHeadphonesConnected() const {
    return m_HasHeadphones;
}
float NuInputDevice::GetVolume() const {
    return m_Volume;
}
unsigned int NuInputDevice::GetSortKey() const {
    return m_SortKey;
}
