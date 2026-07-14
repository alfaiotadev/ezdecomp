#include "nucore/nufpar.h"

static volatile int g_wordUnget = 0;

void NuFParClose(nufpar_s* p) {
    p->file = nullptr;
}

void NuFParUnGetWord(nufpar_s* p) {
    p->wordUnget = g_wordUnget;
}
