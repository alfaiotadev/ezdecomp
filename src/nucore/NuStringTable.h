#pragma once

enum eStringBanks : unsigned int {
    STRINGBANK_0 = 0,
    STRINGBANK_1,
    STRINGBANK_2,
    STRINGBANK_3,
    STRINGBANK_4,
    STRINGBANK_5,
    STRINGBANK_COUNT
};

struct NuStringTableState {
    int field_0;
    eStringBanks bank;
};

__attribute__((visibility("hidden"))) extern NuStringTableState g_NuStringTable;

void NuStringTableSetBank(eStringBanks bank);
eStringBanks NuStringTableGetBank();
