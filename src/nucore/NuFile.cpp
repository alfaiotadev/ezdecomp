#include "nucore/NuFile.h"

NuFile::~NuFile() {}

void NuFile::Init() {}

int NuFile::Read(void* buffer, int size, int count) {
    return 0;
}

void NuFile::Write(const void* data, unsigned long size) {}

long NuFile::Seek(long offset, int whence) {
    return 0;
}

int NuFile::GetPos() {
    return 0;
}

int NuFile::OpenSize() {
    return 0;
}

int NuFileOpenSize(NuFile* const& file) {
    if (file == 0) {
        return 0;
    }
    return file->OpenSize();
}

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}
