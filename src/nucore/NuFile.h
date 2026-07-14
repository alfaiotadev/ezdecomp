#pragma once

class NuFile {
public:
    virtual ~NuFile();
    virtual void Init();
    virtual int Read(void* buffer, int size, int count);
    virtual void Write(const void* data, unsigned long size);
    virtual long Seek(long offset, int whence);
    virtual int GetPos();
    virtual int OpenSize();
};

int NuFileOpenSize(NuFile* const& file);
int NuFileExtPlatformBit(int platform);
