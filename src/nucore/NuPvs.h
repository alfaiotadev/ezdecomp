#pragma once

struct NuPvsData;
struct NuPvsCellHeader;

int NuPvsGetSizeForBits(unsigned int bits);
void NuPvsBitArrayZero(unsigned char* arr, unsigned int bits);
int NuPvsGetCellIdx(const NuPvsData* data, int i, int j);
NuPvsCellHeader* NuPvsGetCellHeader(const NuPvsData* data, int i, int j);
