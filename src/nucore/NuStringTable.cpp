#include "nucore/NuStringTable.h"

static volatile NuStringTable g_stringTable;

static struct {
    char pad[16];
    const char* platformFilter;
    const char* typeFilter;
} g_stringTablePlatformFilter;

eStringBanks NuStringTableGetBank() {
    return g_stringTable.bank;
}

void NuStringTableSetPlatformFilter(const char* filter) {
    g_stringTablePlatformFilter.platformFilter = filter;
}

void NuStringTableSetTypeFilter(const char* filter) {
    g_stringTablePlatformFilter.typeFilter = filter;
}
