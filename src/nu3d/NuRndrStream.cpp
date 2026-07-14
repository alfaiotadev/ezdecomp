#include <cstdint>

__attribute__((visibility("hidden"))) int* g_pNuRndrStreamTotalSize;

int NuRndrStreamGetTotalSize() {
    return *g_pNuRndrStreamTotalSize;
}
