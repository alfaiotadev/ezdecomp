#pragma once

#include "types.h"

int NuAngAdd(int a, int b);
int NuAngWrap(int angle);
int NuAngSub(int a, int b);
void NuAng2AltSol(int* out1, int* out2, int* out3, int a, int b, int c);
float NuAngWrapRads(float angle);
float NuAngAddRads(float a, float b);
float NuAngSubRads(float a, float b);
void NuAngVecAddRads(NUVEC& out, NUVEC const& v1, NUVEC const& b);
void NuAngVecSubRads(NUVEC& out, NUVEC const& v1, NUVEC const& b);
float ApproxSin180(float x);
