#include "nucore/NuFile.h"

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

NuFile::~NuFile() {}

void NuFileClose(NuFile* const& file) {
    delete file;
}
