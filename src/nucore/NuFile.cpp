#include "nucore/NuFile.h"

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

NuFile::~NuFile() {}

long NuFilePos(NuFile* const& file) {
    NuFile* f = file;
    if (f == nullptr) {
        return 0;
    }
    return f->GetPos();
}
