#pragma once

enum eStringBanks {
    kStringBank_Story = 0,
    kStringBank_FreePlay,
    kStringBank_2,
    kStringBank_3,
    kStringBank_4,
    kStringBank_5,
    kStringBank_Count
};

struct NuStringTable {
    int field0;
    eStringBanks bank;
    char pad[2872];
    int format;
};

eStringBanks NuStringTableGetBank();
void NuStringTableSetPlatformFilter(const char* filter);
