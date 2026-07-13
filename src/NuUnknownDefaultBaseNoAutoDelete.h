#pragma once
#include <cstdint>

class NuUnknownDefaultBaseNoAutoDelete {
public:
    NuUnknownDefaultBaseNoAutoDelete();
    virtual ~NuUnknownDefaultBaseNoAutoDelete();
    virtual uint32_t GetRefCount() const;
    virtual uint32_t AddRef();
    virtual uint32_t ReleaseRef();

private:
    int m_instanceCount;
};
