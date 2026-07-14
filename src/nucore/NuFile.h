#pragma once

#include <stddef.h>

class NuFile {
public:
    virtual ~NuFile();
    virtual long Open(const char* filename, int mode) = 0;
    virtual long Read(void* buffer, int size, int count) = 0;
    virtual long Write(const void* buffer, size_t size) = 0;
    virtual long Seek(long offset, int whence) = 0;
};

int NuFileExtPlatformBit(int platform);
void NuFileSeek(NuFile* const& file, long offset, int whence);
