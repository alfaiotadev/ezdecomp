#pragma once

struct NuSpecialData {
    char pad[164];
    unsigned int flags;
};

struct nuhspecial_s {
    void* scene;
    NuSpecialData* data;
};
