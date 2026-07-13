#include "nucore/NuStringTable.h"

static volatile NuStringTable g_stringTable;

eStringBanks NuStringTableGetBank() {
    return g_stringTable.bank;
}
