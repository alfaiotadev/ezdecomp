#include "nucore/NuFile.h"

NuFile::~NuFile() {}

void NuFileGetSortKey(NuFile* const& file, NuFileSortKey& key) {
    NuFile* f = file;
    if (f != nullptr) {
        f->GetSortKey(key);
    }
}

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}
