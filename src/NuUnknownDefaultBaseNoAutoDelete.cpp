#include "NuUnknownDefaultBaseNoAutoDelete.h"

#include <atomic>

NuUnknownDefaultBaseNoAutoDelete::NuUnknownDefaultBaseNoAutoDelete() : m_instanceCount(0) {}
uint32_t NuUnknownDefaultBaseNoAutoDelete::GetRefCount() const {
    return m_instanceCount;
}
uint32_t NuUnknownDefaultBaseNoAutoDelete::AddRef() {
    return __sync_add_and_fetch(&m_instanceCount, 1);
}
uint32_t NuUnknownDefaultBaseNoAutoDelete::ReleaseRef() {
    uint32_t refCount = __sync_sub_and_fetch(&m_instanceCount, 1);
    return refCount;
}