#ifndef NU2API_NUSPECIAL_H
#define NU2API_NUSPECIAL_H

struct NuSpecialObject;

struct nuhspecial_s {
    void* scene;
    NuSpecialObject* object;
};

int NuSpecialGetInstanceix(nuhspecial_s* special);

#endif
