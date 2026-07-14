#pragma once

struct nufpar_s {
    void* file;
};

typedef void NuFParErrorProc(nufpar_s*);
extern NuFParErrorProc* fnInterpreterError;
