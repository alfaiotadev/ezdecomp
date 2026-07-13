#pragma once

#include "numath/types.h"

// 3D Vector Functions
void NuVecNeg(NUVEC* out, NUVEC const* in);
void NuVecAdd(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecSub(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecScale(NUVEC* out, NUVEC const* in, float scale);
void NuVecAddScale(NUVEC* out, NUVEC const* v1, NUVEC const* v2, float scale);
void NuVecScaleAccum(NUVEC* v1, NUVEC const* v2, float scale);
void NuVecInvScale(NUVEC* out, NUVEC const* in, float scale);
void NuVecCross(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecCrossRel(NUVEC* out, NUVEC const* p1, NUVEC const* p2, NUVEC const* ref);
float NuVecDot(NUVEC const* v1, NUVEC const* v2);
void NuVecMax(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecMin(NUVEC* out, NUVEC const* v1, NUVEC const* v2);

// Properties & Normalization
float NuVecMag(NUVEC const* v);
float NuVecMagSqr(NUVEC const* v);
float NuVecMagXZ(NUVEC const* v);
void NuVecNorm(NUVEC* out, NUVEC const* in);
float NuVecNormEx(NUVEC* out, NUVEC const* in);

// Distance & Interpolation
float NuVecDist(NUVEC const* p1, NUVEC const* p2, NUVEC* outDelta);
float NuVecDistSqr(NUVEC const* p1, NUVEC const* p2, NUVEC* outDelta);
float NuVecXZDist(NUVEC const* p1, NUVEC const* p2, NUVEC* outDelta);
float NuVecXZDistSqr(NUVEC const* p1, NUVEC const* p2, NUVEC* out);
void NuVecLerp(NUVEC* out, NUVEC const* start, NUVEC const* end, float t);

// Transformations & Rotations
void NuVecMtxTransform(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecMtxTransformRHLH(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecMtxTransformH(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecMtxTranslate(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecMtxRotate(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecMtxRotateH(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecMtxScale(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecInvMtxTransform(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecInvMtxTranslate(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecInvMtxRotate(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecInvMtxScale(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecMtxRotateValX(NUVEC* out, float val, NUMTX const* m);
void NuVecMtxRotateValY(NUVEC* out, float val, NUMTX const* m);
void NuVecMtxRotateValZ(NUVEC* out, float val, NUMTX const* m);
void NuVecInvMtxRotateValX(NUVEC* out, float val, NUMTX const* m);
void NuVecInvMtxRotateValY(NUVEC* out, float val, NUMTX const* m);
void NuVecInvMtxRotateValZ(NUVEC* out, float val, NUMTX const* m);
void NuVecRotateXOld(NUVEC* out, NUVEC const* in, int angle);
void NuVecRotateXRads(NUVEC* out, NUVEC const* in, float rads);
void NuVecRotateYOld(NUVEC* out, NUVEC const* in, int angle);
void NuVecRotateYRads(NUVEC* out, NUVEC const* in, float rads);
void NuVecRotateZOld(NUVEC* out, NUVEC const* in, int angle);
void NuVecRotateZRads(NUVEC* out, NUVEC const* in, float rads);
void NuVecRotateYValXOld(NUVEC* out, float val, int angle);
void NuVecRotateYValXRads(NUVEC* out, float val, float rads);
void NuVecRotateYValZOld(NUVEC* out, float val, int angle);
void NuVecRotateYValZRads(NUVEC* out, float val, float rads);

// Utility & Conversion
void NuVecSurfaceNormal(NUVEC* out, NUVEC const* p1, NUVEC const* p2, NUVEC const* p3);
bool NuVecCompareTolerance(NUVEC const* v1, NUVEC const* v2, float tolerance);
void NuVecToNuHalfVec(NUVEC const* in, NUHALFVEC* out);
void NuHalfVecToNuVec(NUHALFVEC const* in, NUVEC* out);
void NuMtxVecToEulerXYZOld(NUVEC const* fwd, NUVEC const* up, int* x, int* y, int* z);
void NuMtxVecToEulerXYZRads(NUVEC const* fwd, NUVEC const* up, float* x, float* y, float* z);
void NuAngVecAddRads(NUVEC& out, NUVEC const& v1, NUVEC const& v2);
void NuAngVecSubRads(NUVEC& out, NUVEC const& v1, NUVEC const& v2);

// 4D Vector Functions (NUVEC4)
void NuVec4Add(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2);
void NuVec4Sub(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2);
void NuVec4Scale(NUVEC4* out, NUVEC4 const* in, float scale);
void NuVec4AddScale(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2, float scale);
float NuVec4Dot(NUVEC4 const* v1, NUVEC4 const* v2);
void NuVec4MtxTransform(NUVEC4* out, NUVEC const* v, NUMTX const* m);
void NuVec4MtxTransformH(NUVEC4* out, NUVEC4 const* v, NUMTX const* m);
void NuVec4Max(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2);
void NuVec4Min(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2);
float NuVec4Mag(NUVEC4 const* v);
float NuVec4MagSqr(NUVEC4 const* v);
void NuVec4Lerp(NUVEC4* out, NUVEC4 const* start, NUVEC4 const* end, float t);
void NuVec4ToNuHalfVec4(NUVEC4 const* in, NUHALFVEC4* out);
void NuHalfVec4ToNuVec4(NUHALFVEC4 const* in, NUVEC4* out);
bool NuVec4CompareTolerance(NUVEC4 const* v1, NUVEC4 const* v2, float tolerance);

// SIMD Accelerated Vector Functions
void NuVec4MtxTransformVU0(NUVEC4* out, NUVEC4 const* v, NUMTX const* m);
void NuVecMtxTransformVU0(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVecInvMtxTransformVU0(NUVEC* out, NUVEC const* v, NUMTX const* m);
void NuVec4MtxRotateVU0(NUVEC4* out, NUVEC4 const* v, NUMTX const* m);
void NuVec4ScaleXYZVU0(NUVEC4* out, NUVEC4 const* in, float scale);
float NuVecMagVU0(NUVEC const* v);
