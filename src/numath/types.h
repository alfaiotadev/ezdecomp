#pragma once
#include <cstdint>

struct NUVEC {
    float x;
    float y;
    float z;
};
struct NUVEC4 {
    float x;
    float y;
    float z;
    float w;
};
struct NUMTX {
    float m[4][4];
};
struct NUQUAT {
    float x;
    float y;
    float z;
    float w;
};

struct NUHALFVEC {
    uint16_t x;
    uint16_t y;
    uint16_t z;
};
struct NUHALFVEC4 {
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t w;
};
struct NUPLANE {
    NUVEC normal;
    float d;
};
struct NUANGVEC {
    int x;
    int y;
    int z;
};
