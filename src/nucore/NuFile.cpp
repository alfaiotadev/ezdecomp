#include "nucore/NuFile.h"

NuFile::~NuFile() {}

void NuFileSeek(NuFile* const& file, long offset, int whence) {
    if (file == NULL) {
        return;
    }
    file->Seek(offset, whence);
}

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}
