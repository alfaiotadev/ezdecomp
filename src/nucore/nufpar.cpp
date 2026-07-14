#include "nucore/nufpar.h"

NuFParErrorProc* fnInterpreterError;

void NuFParClose(nufpar_s* p) {
    p->file = nullptr;
}

NuFParErrorProc* NuFParSetInterpreterErrorHandler(NuFParErrorProc* handler) {
    NuFParErrorProc* prev = fnInterpreterError;
    fnInterpreterError = handler;
    return prev;
}
