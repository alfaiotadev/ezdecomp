#include "nucore/nufpar.h"

void NuFParClose(nufpar_s* p) {
    p->file = nullptr;
}

void NuUnGetChar(nufpar_s* p) {
    if (p != nullptr && p->pos > 0) {
        p->pos--;
    }
}
