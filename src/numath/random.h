#pragma once

struct nunrand_s {
    unsigned int seed;
};

static nunrand_s g_defaultNuRandState;
extern unsigned int fseed;

void NuRandSeed(unsigned int seed);
unsigned int NuRandGetSeed();
void NuRandNextSeed(unsigned int* seed);
float NuRandFloatSeeded(unsigned int* seed);
float NuRandFloat();
float NuRandFloatInRange(float min, float max);
unsigned int NuRandIntSeeded(unsigned int* seed);
unsigned int NuRandInt();
int NuRandIntInRange(unsigned int min, unsigned int max);
int NuRandInt(unsigned int min, unsigned int max);
void NuRandSetSeed(nunrand_s* state, int newSeed);
unsigned int NuRand(nunrand_s* state = nullptr);
float NuFloatRand(nunrand_s* state = nullptr);
