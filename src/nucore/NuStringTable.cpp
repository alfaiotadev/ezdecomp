#include "nucore/NuStringTable.h"

static volatile NuStringTable g_stringTable;

static struct {
    char pad[16];
    const char* platformFilter;
} g_stringTablePlatformFilter;

eStringBanks NuStringTableGetBank() {
    return g_stringTable.bank;
}

void NuStringTableSetPlatformFilter(const char* filter) {
    g_stringTablePlatformFilter.platformFilter = filter;
}
