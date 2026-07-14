#include "nucore/NuFile.h"

class NuFileReadCache {
public:
    void CacheFile(const char*);
};

struct NuFileReadCacheHolder {
    char pad[0x30];
    NuFileReadCache cache;
};

static NuFileReadCacheHolder g_NuFileReadCacheHolder;

void NuFileCacheFile(const char* name) {
    g_NuFileReadCacheHolder.cache.CacheFile(name);
}

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}
