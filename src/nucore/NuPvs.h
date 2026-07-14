#pragma once

struct NuPvsData;

int NuPvsGetSizeForBits(unsigned int bits);
void NuPvsBitArrayZero(unsigned char* arr, unsigned int bits);
int NuPvsGetCellIdx(const NuPvsData* data, int i, int j);
int NuPvsGetActiveCellVolume(void);
