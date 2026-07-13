#pragma once

#include <numath/types.h>

extern NUMTX numtx_zero;
extern NUMTX numtx_identity;

// Initialization
void NuMtxSetZero(NUMTX* out);
void NuMtxSetIdentity(NUMTX* out);
void NuMtxSetTranslation(NUMTX* out, NUVEC const* translation);
void NuMtxSetTranslationNeg(NUMTX* out, NUVEC const* translation);
void NuMtxSetScale(NUMTX* out, NUVEC const* scale);
void NuMtxSetRotationXOld(NUMTX* out, int angle);
void NuMtxSetRotationXRads(NUMTX* out, float rads);
void NuMtxSetRotationYOld(NUMTX* out, int angle);
void NuMtxSetRotationYRads(NUMTX* out, float rads);
void NuMtxSetRotationZOld(NUMTX* out, int angle);
void NuMtxSetRotationZRads(NUMTX* out, float rads);
void NuMtxSetRotationAxisOld(NUMTX* out, int angle, NUVEC const* axis);
void NuMtxSetRotationAxisRads(NUMTX* out, float rads, NUVEC const* axis);
void NuMtxSetRotateXYZOld(NUMTX* out, NUANGVEC const* angles);
void NuMtxSetRotateXYZRads(NUMTX* out, NUVEC const* rads);
void NuMtxSetRotateYXZOld(NUMTX* out, NUANGVEC const* angles);
void NuMtxSetRotateYXZRads(NUMTX* out, NUVEC const* rads);
void NuMtxSkewSymmetric(NUMTX* out, NUVEC const* vec);

// Modification
void NuMtxTranslate(NUMTX* mtx, NUVEC const* translation);
void NuMtxTranslateNeg(NUMTX* mtx, NUVEC const* translation);
void NuMtxScale(NUMTX* mtx, NUVEC const* scale);
void NuMtxScaleU(NUMTX* mtx, float scale);
void NuMtxRotateXOld(NUMTX* mtx, int angle);
void NuMtxRotateXRads(NUMTX* mtx, float rads);
void NuMtxRotateYOld(NUMTX* mtx, int angle);
void NuMtxRotateYRads(NUMTX* mtx, float rads);
void NuMtxRotateZOld(NUMTX* mtx, int angle);
void NuMtxRotateZRads(NUMTX* mtx, float rads);

// Modification (Pre-Multiplication)
void NuMtxPreTranslate(NUMTX* mtx, NUVEC const* translation);
void NuMtxPreTranslateX(NUMTX* mtx, float x);
void NuMtxPreTranslateNeg(NUMTX* mtx, NUVEC const* translation);
void NuMtxPreScale(NUMTX* mtx, NUVEC const* scale);
void NuMtxPreScaleU(NUMTX* mtx, float scale);
void NuMtxPreScaleX(NUMTX* mtx, float x);
void NuMtxPreSkewYX(NUMTX* mtx, float skew);
void NuMtxPreRotateXOld(NUMTX* mtx, int angle);
void NuMtxPreRotateXRads(NUMTX* mtx, float rads);
void NuMtxPreRotateYOld(NUMTX* mtx, int angle);
void NuMtxPreRotateYRads(NUMTX* mtx, float rads);
void NuMtxPreRotateY180(NUMTX* mtx);
void NuMtxPreRotateZOld(NUMTX* mtx, int angle);
void NuMtxPreRotateZRads(NUMTX* mtx, float rads);

// Core Arithmetic & Algebra
void NuMtxMul(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs);
void NuMtxMulH(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs);
void NuMtxMulR(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs);
void NuMtxAddR(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs);
void NuMtxSubR(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs);
void NuMtxTranspose(NUMTX* out, NUMTX const* src);
void NuMtxTransposeR(NUMTX* out, NUMTX const* src);
void NuMtxInv(NUMTX* out, NUMTX const* src);
void NuMtxInvR(NUMTX* out, NUMTX const* src);
void NuMtxInvRSS(NUMTX* out, NUMTX const* src);
void NuMtxInvTranspose3x3(NUMTX* out, NUMTX const* src);
void NuMtxInvRSSH(NUMTX* out, NUMTX const* src);
void NuMtxInvH(NUMTX* out, NUMTX const* src);
void NuMtxInvHOld(NUMTX* out, NUMTX const* src);

// View / Camera Matrices
void NuMtxAlignX(NUMTX* out, NUVEC const* vec);
void NuMtxAlignY(NUMTX* out, NUVEC const* vec);
void NuMtxAlignZ(NUMTX* out, NUVEC const* vec);
void NuMtxLookAtX(NUMTX* out, NUVEC const* target);
void NuMtxLookAtY(NUMTX* out, NUVEC const* target);
void NuMtxLookAtZ(NUMTX* out, NUVEC const* target);
void NuMtxInvLookAtX(NUMTX* out, NUVEC const* target);
void NuMtxInvLookAtY(NUMTX* out, NUVEC const* target);
void NuMtxInvLookAtZ(NUMTX* out, NUVEC const* target);
void NuMtxLookAtD3D(NUMTX* out, NUVEC const* eye, NUVEC const* at, NUVEC const* up);
void NuMtxLookAtInverseD3D(NUMTX* out, NUVEC const* eye, NUVEC const* at, NUVEC const* up);

// Projection Matrices
void NuMtxSetPerspectiveD3D(NUMTX* out, float fovY, float aspect, float zNear, float zFar);
void NuMtxSetPerspectiveD3DWH(NUMTX* out, float width, float height, float zNear, float zFar);
void NuMtxSetPerspectiveBlend(NUMTX* out, float fovY, float aspect, float zNear, float zFar);
void NuMtxSetFrustumD3D(NUMTX* out, float l, float r, float b, float t, float n, float f);
void NuMtxSetFrustumBlend(NUMTX* out, float l, float r, float b, float t, float n, float f);
void NuMtxSetOrthoD3D(NUMTX* out, float l, float r, float b, float t, float n, float f);
void NuMtxSetOrthoBlend(NUMTX* out, float l, float r, float b, float t, float n, float f);

// Data Extraction / Getters
NUVEC NuMtxGetScale(NUMTX const* mtx);
void NuMtxGetXAxis(NUMTX const* mtx, NUVEC* outAxis);
void NuMtxGetYAxis(NUMTX const* mtx, NUVEC* outAxis);
void NuMtxGetZAxis(NUMTX const* mtx, NUVEC* outAxis);
void NuMtxGetTranslation(NUMTX const* mtx, NUVEC* outTranslation);
bool NuMtxGetHandiness(NUMTX const* mtx);
void NuMtxVecToEulerXYZOld(NUVEC const* xAxis, NUVEC const* zAxis, int* outX, int* outY, int* outZ);
void NuMtxGetEulerXYZOld(NUMTX const* mtx, int* outX, int* outY, int* outZ);
void NuMtxGetEulerXYZRads(NUMTX const* mtx, float* outX, float* outY, float* outZ);
void NuMtxGetEulerAngVecRads(NUMTX const& mtx, NUVEC& outAngVec);
void NuMtxGetOrthoD3D(NUMTX const* mtx, float* l, float* r, float* b, float* t, float* n, float* f);
void NuMtxGetPerspectiveD3D(NUMTX const* mtx, float* fovY, float* aspect, float* zNear, float* zFar);
void NuMtxGetPerspectiveBlend(NUMTX const* mtx, float* fovY, float* aspect, float* zNear, float* zFar);
void NuMtxGetFrustumD3D(NUMTX const* mtx, float* l, float* r, float* b, float* t, float* n, float* f);
void NuMtxGetFrustumBlend(NUMTX const* mtx, float* l, float* r, float* b, float* t, float* n, float* f);

// SIMD Functions
void NuMtxSetRotateXYZVU0(NUMTX* out, NUANGVEC const* angles);
void NuMtxPreScaleVU0(NUMTX* mtx, NUVEC const* scale);
void NuMtxMulVU0(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs);
void NuMtxInvVU0(NUMTX* out, NUMTX const* src);
void NuMtxSetRotationXYVU0(NUMTX* out, NUANGVEC const* angles);

// Utility & Miscellaneous
void NuMtxOrth(NUMTX* mtx);
NUVEC NuMtxNormalise(NUMTX* out, NUMTX const* src, bool* was_normalised);
float NuMtxDet3(NUMTX const* mtx);
int NuMtxCompare(NUMTX const* m1, NUMTX const* m2);
float NuMtxSSE(NUMTX const* m1, NUMTX const* m2);
void NuMtxTruncate24Bit(NUMTX* out, NUMTX const* src);
void NuMtx24BitCorrection(NUMTX* out, NUMTX const* src);
void NuMtxPrint(NUMTX const* mtx);
void NuMtxRotateOld(int angle, float x, float y, float* outX, float* outY);
void NuMtxRotateRads(float rads, float x, float y, float* outX, float* outY);
