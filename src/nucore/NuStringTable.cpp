#include "nucore/NuStringTable.h"

void NuStringTableSetBank(eStringBanks bank) {
    if (bank > static_cast<eStringBanks>(5)) {
        return;
    }
    g_NuStringTable.bank = bank;
}

eStringBanks NuStringTableGetBank() {
    return g_NuStringTable.bank;
}
