#pragma once

#include <numath/types.h>

float NuQuatMagnitude(NUQUAT const* q);
float NuQuatDot(NUQUAT const* a, NUQUAT const* b);
void NuQuatNeg2(NUQUAT* out, NUQUAT* in);
void NuQuatAdd(NUQUAT* out, NUQUAT const* a, NUQUAT const* b);
void NuQuatSub(NUQUAT* out, NUQUAT const* a, NUQUAT const* b);
void NuQuatScaleAccum(NUQUAT* out, NUQUAT const* in, float scale);
void NuQuatInv(NUQUAT* out, NUQUAT const* in);
void NuQuatHarmonize(NUQUAT const* a, NUQUAT* out);
void NuQuatLerp(NUQUAT* out, NUQUAT const* a, NUQUAT const* b, float t);
void NuQuatBlend(NUQUAT* out, NUQUAT const* a, NUQUAT const* b, float t1, float t2);
void NuQuatMul(NUQUAT* out, NUQUAT const* a, NUQUAT const* b);
void NuQuatNormalise(NUQUAT* out, NUQUAT const* in);
void NuQuatToMtx(NUQUAT const* q, NUMTX* out);
void NuQuatToMtx(NUQUAT const* q, NUMTX* out);
void NuQuatFromEulerXYZ(NUQUAT* out, int x, int y, int z);
void NuQuatFromEulerRadsXYZ(NUQUAT* out, float x, float y, float z);
void NuQuatFromEulerVecRads(NUQUAT& out, NUVEC const& v);
void NuMtxToQuat(NUMTX const* mtx, NUQUAT* out);
void NuMtxToQuatRH(NUMTX const* mtx, NUQUAT* out);
void NuEulerVecFromQuatRads(NUQUAT const& q, NUVEC& out);
void NuEulerXYZFromQuat(int* x, int* y, int* z, NUQUAT const* q);
void NuQuatSlerp(NUQUAT* out, NUQUAT const* a, NUQUAT const* b, float t);
void NuQuatHermiteInt(NUQUAT* out, NUQUAT* a, NUQUAT* b, NUQUAT* c, NUQUAT* d, float t);
void NuQuatCubicInt(NUQUAT* out, NUQUAT* a, NUQUAT* b, NUQUAT* c, NUQUAT* d, float t);
