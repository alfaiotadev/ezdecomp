#pragma once

struct nufpar_s {
    void* file;
    char pad[0xAC0];
    int comcnt;
};
