#pragma once

enum class NuFileDeviceType : int {
    kNone = 0,
};

class NuFileDevice {
public:
    static NuFileDevice* sm_DefaultDevice;
    void* vtable;
    int field_8;
    NuFileDeviceType m_type;
};
