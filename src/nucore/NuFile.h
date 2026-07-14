#pragma once

class NuFile {
public:
    virtual ~NuFile();
    virtual void Close() = 0;
    virtual int Read(void* buffer, int size, int count) = 0;
    virtual int Write(const void* buffer, unsigned long size) = 0;
    virtual long Seek(long offset, int origin) = 0;
    virtual long GetPos() = 0;
    virtual long GetSize() = 0;
};

int NuFileExtPlatformBit(int platform);
long NuFilePos(NuFile* const& file);
