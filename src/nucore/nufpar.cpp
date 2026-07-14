#include "nucore/nufpar.h"

void NuFParClose(nufpar_s* p) {
    p->file = nullptr;
}

void NuFParPopCom(nufpar_s* p) {
    if (p->comcnt >= 0) {
        p->comcnt--;
    }
}
