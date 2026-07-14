#pragma once

struct nufpar_s {
    void* file;
    char pad[2348];
    int wordUnget;
};
