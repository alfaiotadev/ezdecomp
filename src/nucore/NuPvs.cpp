#include "nucore/NuPvs.h"

#include <string.h>

struct NuPvsData {
    char pad0[28];
    int xCellCount;
};

struct NuPvsZoneBox;
struct NuPvsCellVolumeUnpacked;
struct NuPvsCellVolume;

struct NuPvsGlobals {
    void* unk0;
    NuPvsCellVolume* activeCellVolume;
};

struct NuPvsCellVolume {
    NuPvsData* data;
    char pad0[32];
    void* activeZone;
    char pad1[12];
    unsigned char flags;
};

__attribute__((visibility("hidden"))) NuPvsGlobals s_pvs;

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

int NuPvsGetActiveCellVolume(void) {
    return s_pvs.activeCellVolume->flags & 1;
}
