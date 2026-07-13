#pragma once
#include <cstdint>

class NuUnknownDefaultBase {
public:
    NuUnknownDefaultBase();
    virtual ~NuUnknownDefaultBase();
    virtual uint32_t GetRefCount() const;
    virtual uint32_t AddRef();
    virtual uint32_t ReleaseRef();

private:
    int m_instanceCount;
};
