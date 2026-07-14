#include "numath/types.h"
#include <string.h>

void NuQFntSetMtxRS(void* obj, NUMTX const* mtx) {
    memcpy(((char*)*(void**)((char*)obj + 0x80)) + 0x10, mtx, sizeof(NUMTX));
}
