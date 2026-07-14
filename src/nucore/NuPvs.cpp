#include "nucore/NuPvs.h"

#include <string.h>

struct NuPvsCellHeader {
    char pad[16];
};

struct NuPvsData {
    char pad0[28];
    int xCellCount;
    char pad1[8];
    NuPvsCellHeader* cellHeaders;
};

struct NuPvsZoneBox;
struct NuPvsCellVolumeUnpacked;

int NuPvsGetSizeForBits(unsigned int bits) {
    return (bits >> 3) + 1;
}

int NuPvsIsVisible(unsigned short) {
    return 1;
}

int NuPvsIsVisible(const NuPvsData*, const NuPvsZoneBox*, int) {
    return 1;
}

int NuPvsIsVisible(const NuPvsData*, const NuPvsCellVolumeUnpacked*, int) {
    return 1;
}

void NuPvsBitArrayZero(unsigned char* arr, unsigned int bits) {
    memset(arr, 0, (bits >> 3) + 1);
}

int NuPvsGetCellIdx(const NuPvsData* data, int i, int j) {
    return data->xCellCount * j + i;
}

NuPvsCellHeader* NuPvsGetCellHeader(const NuPvsData* data, int i, int j) {
    return &data->cellHeaders[data->xCellCount * j + i];
}
