#include "NuUnknownDefaultBase.h"

#include <atomic>

NuUnknownDefaultBase::NuUnknownDefaultBase() : m_instanceCount(0) {}
uint32_t NuUnknownDefaultBase::GetRefCount() const {
    return m_instanceCount;
}
uint32_t NuUnknownDefaultBase::AddRef() {
    return __sync_add_and_fetch(&m_instanceCount, 1);
}
uint32_t NuUnknownDefaultBase::ReleaseRef() {
    uint32_t refCount = __sync_sub_and_fetch(&m_instanceCount, 1);
    if (refCount == 0) {
        delete this;
    }
    return refCount;
}
