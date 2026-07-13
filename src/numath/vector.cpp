#include "numath/scalar.h"
#include "numath/vector.h"
#include <math.h>

void NuVecNeg(NUVEC* out, NUVEC const* in) {
    out->x = -in->x;
    out->y = -in->y;
    out->z = -in->z;
}
void NuVecAdd(NUVEC* out, NUVEC const* v1, NUVEC const* v2) {
    out->x = v1->x + v2->x;
    out->y = v1->y + v2->y;
    out->z = v1->z + v2->z;
}
void NuVecSub(NUVEC* out, NUVEC const* v1, NUVEC const* v2) {
    out->x = v1->x - v2->x;
    out->y = v1->y - v2->y;
    out->z = v1->z - v2->z;
}
void NuVecScale(NUVEC* out, NUVEC const* in, float scale) {
    out->x = in->x * scale;
    out->y = in->y * scale;
    out->z = in->z * scale;
}
void NuVecAddScale(NUVEC* out, NUVEC const* v1, NUVEC const* v2, float scale) {
    out->x = v1->x + v2->x * scale;
    out->y = v1->y + v2->y * scale;
    out->z = v1->z + v2->z * scale;
}
void NuVecScaleAccum(NUVEC* v1, NUVEC const* v2, float scale) {
    v1->x += v2->x * scale;
    v1->y += v2->y * scale;
    v1->z += v2->z * scale;
}
void NuVecInvScale(NUVEC* out, NUVEC const* in, float scale) {
    if (scale == 0.0f) {
        scale = 0.0f;
    } else {
        scale = 1.0f / scale;
    }
    NuVecScale(out, in, scale);
}
void NuVecCross(NUVEC* out, NUVEC const* v1, NUVEC const* v2) {
    float y = v1->z * v2->x - v1->x * v2->z;
    float z = v1->x * v2->y - v1->y * v2->x;
    float x = v1->y * v2->z - v1->z * v2->y;
    out->x = x;
    out->y = y;
    out->z = z;
}
void NuVecCrossRel(NUVEC* out, NUVEC const* p1, NUVEC const* p2, NUVEC const* ref) {
    float y = (p2->z - p1->z) * (ref->x - p1->x) - (p2->x - p1->x) * (ref->z - p1->z);
    float z = (p2->x - p1->x) * (ref->y - p1->y) - (ref->x - p1->x) * (p2->y - p1->y);
    float x = (ref->z - p1->z) * (p2->y - p1->y) - (p2->z - p1->z) * (ref->y - p1->y);
    out->x = x;
    out->y = y;
    out->z = z;
}
float NuVecDot(NUVEC const* v1, NUVEC const* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}
void NuVecSurfaceNormal(NUVEC* out, NUVEC const* p1, NUVEC const* p2, NUVEC const* p3) {
    NUVEC e1, e2;
    NuVecSub(&e1, p1, p2);
    NuVecSub(&e2, p1, p3);
    NuVecCross(out, &e2, &e1);
    NuVecNorm(out, out);
}
void NuVecMax(NUVEC* out, NUVEC const* v1, NUVEC const* v2) {
    out->x = v1->x > v2->x ? v1->x : v2->x;
    out->y = v1->y > v2->y ? v1->y : v2->y;
    out->z = v1->z > v2->z ? v1->z : v2->z;
}
void NuVecMin(NUVEC* out, NUVEC const* v1, NUVEC const* v2) {
    out->x = v1->x < v2->x ? v1->x : v2->x;
    out->y = v1->y < v2->y ? v1->y : v2->y;
    out->z = v1->z < v2->z ? v1->z : v2->z;
}
float NuVecMag(const NUVEC* v) {
    return NuFsqrt(NuVecDot(v, v));
}
float NuVecMagSqr(NUVEC const* v) {
    return NuVecDot(v, v);
}
float NuVecMagXZ(const NUVEC* v) {
    return NuFsqrt(v->x * v->x + v->z * v->z);
}
void NuVecNorm(NUVEC* out, NUVEC const* in) {
    float sq = NuVecMagSqr(in);
    float invMag;

    if (sq <= 0.0f) {
        invMag = 0.0f;
    } else {
        invMag = 1.0f / sqrtf(sq);
    }
    float x = in->x * invMag;
    float y = in->y * invMag;
    float z = in->z * invMag;
    out->x = x;
    out->y = y;
    out->z = z;
}
float NuVecNormEx(NUVEC* out, NUVEC const* in) {
    float mag = NuFsqrt(in->x * in->x + in->y * in->y + in->z * in->z);
    float invMag;

    if (mag > 0.0f) {
        invMag = 1.0f / mag;
    } else {
        invMag = 0.0f;
    }
    float x = in->x;
    float y = in->y;
    float z = in->z;
    out->x = x * invMag;
    out->y = invMag * y;
    out->z = z * invMag;

    return mag;
}
bool NuVecCompareTolerance(NUVEC const* v1, NUVEC const* v2, float tolerance) {
    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;
    float dz = v1->z - v2->z;
    return !(NuFsqrt(dx * dx + dy * dy + dz * dz) > tolerance);
}
float NuVecDist(NUVEC const* p1, NUVEC const* p2, NUVEC* outDelta) {
    NUVEC delta;
    if (outDelta != nullptr) {
        NuVecSub(outDelta, p1, p2);
        return NuVecMag(outDelta);
    }
    NuVecSub(&delta, p1, p2);
    return NuVecMag(&delta);
}
float NuVecDistSqr(NUVEC const* p1, NUVEC const* p2, NUVEC* outDelta) {
    NUVEC delta;
    if (outDelta != nullptr) {
        NuVecSub(outDelta, p1, p2);
        return NuVecMagSqr(outDelta);
    }
    NuVecSub(&delta, p1, p2);
    return NuVecMagSqr(&delta);
}
float NuVecXZDist(NUVEC const* p1, NUVEC const* p2, NUVEC* outDelta) {
    NUVEC delta;
    if (outDelta != nullptr) {
        outDelta->x = p1->x - p2->x;
        outDelta->y = 0.0f;
        outDelta->z = p1->z - p2->z;
        return NuVecMag(outDelta);
    }
    delta.x = p1->x - p2->x;
    delta.y = 0.0f;
    delta.z = p1->z - p2->z;
    return NuVecMag(&delta);
}
float NuVecXZDistSqr(NUVEC const* p1, NUVEC const* p2, NUVEC* out) {
    NUVEC delta;
    if (out != nullptr) {
        out->x = p1->x - p2->x;
        out->y = 0.0f;
        out->z = p1->z - p2->z;
        return NuVecMagSqr(out);
    }
    delta.x = p1->x - p2->x;
    delta.y = 0.0f;
    delta.z = p1->z - p2->z;
    return NuVecMagSqr(&delta);
}
void NuVecLerp(NUVEC* out, NUVEC const* end, NUVEC const* start, float t) {
    out->x = (end->x - start->x) * t + start->x;
    out->y = (end->y - start->y) * t + start->y;
    out->z = (end->z - start->z) * t + start->z;
}
void NuVecMtxTransform(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0] + m->m[3][0];
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1] + m->m[3][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2] + m->m[3][2];

    out->x = x;
    out->y = y;
    out->z = z;
}
void NuVecMtxTransformH(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float w = v->x * m->m[0][3] + v->y * m->m[1][3] + v->z * m->m[2][3] + m->m[3][3];
    float inv = w == 0.0f ? 0.0f : 1.0f / w;
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0] + m->m[3][0];
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1] + m->m[3][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2] + m->m[3][2];

    out->x = x * inv;
    out->y = y * inv;
    out->z = z * inv;
}
void NuVecMtxTransformRHLH(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] - v->z * m->m[2][1] + m->m[3][1];
    float z = -(v->x * m->m[0][2]) - v->y * m->m[1][2] + v->z * m->m[2][2] - m->m[3][2];
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] - v->z * m->m[2][0] + m->m[3][0];

    out->x = x;
    out->y = y;
    out->z = z;
}
void NuVecMtxTranslate(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    out->x = v->x + m->m[3][0];
    out->y = v->y + m->m[3][1];
    out->z = v->z + m->m[3][2];
}
void NuVecMtxRotate(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0];
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2];

    out->x = x;
    out->y = y;
    out->z = z;
}
void NuVecMtxRotateH(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float w = v->x * m->m[0][3] + v->y * m->m[1][3] + v->z * m->m[2][3];
    float inv = 1.0f / w;
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0];
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2];

    out->x = x * inv;
    out->y = y * inv;
    out->z = z * inv;
}
void NuVecInvMtxRotate(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float y = v->x * m->m[1][0] + v->y * m->m[1][1] + v->z * m->m[1][2];
    float z = v->x * m->m[2][0] + v->y * m->m[2][1] + v->z * m->m[2][2];
    float x = v->x * m->m[0][0] + v->y * m->m[0][1] + v->z * m->m[0][2];

    out->x = x;
    out->y = y;
    out->z = z;
}
void NuVecInvMtxTransform(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float dx = v->x - m->m[3][0];
    float dy = v->y - m->m[3][1];
    float dz = v->z - m->m[3][2];
    out->x = dx * m->m[0][0] + dy * m->m[0][1] + dz * m->m[0][2];
    out->y = dx * m->m[1][0] + dy * m->m[1][1] + dz * m->m[1][2];
    out->z = dx * m->m[2][0] + dy * m->m[2][1] + dz * m->m[2][2];
}
void NuVecMtxScale(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    out->x = v->x * m->m[0][0];
    out->y = v->y * m->m[1][1];
    out->z = v->z * m->m[2][2];
}
void NuVecInvMtxTranslate(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    out->x = v->x - m->m[3][0];
    out->y = v->y - m->m[3][1];
    out->z = v->z - m->m[3][2];
}
void NuVecInvMtxScale(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    out->x = v->x / m->m[0][0];
    out->y = v->y / m->m[1][1];
    out->z = v->z / m->m[2][2];
}
void NuVecMtxRotateValX(NUVEC* out, float val, NUMTX const* m) {
    out->x = m->m[0][0] * val;
    out->y = m->m[0][1] * val;
    out->z = m->m[0][2] * val;
}
void NuVecMtxRotateValY(NUVEC* out, float val, NUMTX const* m) {
    out->x = m->m[1][0] * val;
    out->y = m->m[1][1] * val;
    out->z = m->m[1][2] * val;
}
void NuVecMtxRotateValZ(NUVEC* out, float val, NUMTX const* m) {
    out->x = m->m[2][0] * val;
    out->y = m->m[2][1] * val;
    out->z = m->m[2][2] * val;
}
void NuVecInvMtxRotateValX(NUVEC* out, float val, NUMTX const* m) {
    out->x = out->x * m->m[0][0];
    out->y = out->x * m->m[1][0];
    out->z = out->x * m->m[2][0];
}
void NuVecInvMtxRotateValY(NUVEC* out, float val, NUMTX const* m) {
    out->x = out->y * m->m[0][1];
    out->y = out->y * m->m[1][1];
    out->z = out->y * m->m[2][1];
}
void NuVecInvMtxRotateValZ(NUVEC* out, float val, NUMTX const* m) {
    out->x = out->z * m->m[0][2];
    out->y = out->z * m->m[1][2];
    out->z = out->z * m->m[2][2];
}
void NuVecRotateXOld(NUVEC* out, NUVEC const* in, int angle) {
    float angleCos = NuSinOld(angle + 16384);
    float angleSin = NuSinOld(angle);

    float x_val = in->x;
    float y = in->y;
    out->x = x_val;
    float z = in->z;

    float temp1 = angleCos * y;
    float temp2 = angleSin * y;
    float temp3 = angleSin * z;

    out->y = temp1 - temp3;

    float temp4 = angleCos * z;
    out->z = temp2 + temp4;
}
void NuVecToNuHalfVec(NUVEC const* in, NUHALFVEC* out) {
    out->x = NuFloatToHalf(in->x);
    out->y = NuFloatToHalf(in->y);
    out->z = NuFloatToHalf(in->z);
}

static inline float NuHalfToFloat(uint16_t h) {
    float result;
    if (h == 0) {
        result = 0.0f;
    } else {
        uint32_t u = ((h & 0x8000) << 16) | (((h & 0x7C00) + 0x1C000) << 13) | ((h & 0x03FF) << 13);
        result = *(float*)&u;
    }
    return result;
}

void NuHalfVecToNuVec(NUHALFVEC const* in, NUVEC* out) {
    out->x = NuHalfToFloat(in->x);
    out->y = NuHalfToFloat(in->y);
    out->z = NuHalfToFloat(in->z);
}
void NuVecRotateXRads(NUVEC* out, NUVEC const* in, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float y = in->y;
    out->x = in->x;
    float z = in->z;
    out->y = c * y - s * z;
    out->z = s * y + c * z;
}
void NuVecRotateYRads(NUVEC* out, NUVEC const* in, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float x = in->x;
    float z = in->z;
    out->x = c * x + s * z;
    out->y = in->y;
    out->z = c * z - s * x;
}
void NuVecRotateZRads(NUVEC* out, NUVEC const* in, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float x = in->x;
    float y = in->y;
    out->x = c * x - s * y;
    out->y = s * x + c * y;
    out->z = in->z;
}
void NuVecRotateYValXRads(NUVEC* out, float val, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    out->x = c * val;
    out->y = 0.0f;
    out->z = -(s * val);
}
void NuVecRotateYValZRads(NUVEC* out, float val, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    out->x = s * val;
    out->y = 0.0f;
    out->z = c * val;
}
void NuVecRotateYValXOld(NUVEC* out, float val, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    out->x = c * val;
    out->y = 0.0f;
    out->z = -(s * val);
}
void NuVecRotateYValZOld(NUVEC* out, float val, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    out->x = s * val;
    out->y = 0.0f;
    out->z = c * val;
}
void NuVecRotateYOld(NUVEC* out, NUVEC const* in, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float x = in->x;
    float z = in->z;
    out->x = c * x + s * z;
    out->y = in->y;
    out->z = c * z - s * x;
}
void NuVecRotateZOld(NUVEC* out, NUVEC const* in, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float x = in->x;
    float y = in->y;
    out->x = c * x - s * y;
    out->y = s * x + c * y;
    out->z = in->z;
}
bool NuVec4CompareTolerance(NUVEC4 const* v1, NUVEC4 const* v2, float tolerance) {
    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;
    float dz = v1->z - v2->z;
    float dw = v1->w - v2->w;
    return !(NuFsqrt(dx * dx + dw * dw + dy * dy + dz * dz) > tolerance);
}
void NuVec4MtxTransform(NUVEC4* out, NUVEC const* v, NUMTX const* m) {
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1] + m->m[3][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2] + m->m[3][2];
    float w = v->x * m->m[0][3] + v->y * m->m[1][3] + v->z * m->m[2][3] + m->m[3][3];
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0] + m->m[3][0];

    out->x = x;
    out->y = y;
    out->z = z;
    out->w = w;
}
void NuVec4MtxTransformH(NUVEC4* out, NUVEC4 const* v, NUMTX const* m) {
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0] + v->w * m->m[3][0];
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1] + v->w * m->m[3][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2] + v->w * m->m[3][2];
    float w = v->x * m->m[0][3] + v->y * m->m[1][3] + v->z * m->m[2][3] + v->w * m->m[3][3];

    out->x = x;
    out->y = y;
    out->z = z;
    out->w = w;
}
void NuVec4MtxTransformVU0(NUVEC4* out, NUVEC4 const* v, NUMTX const* m) {
    NuVec4MtxTransformH(out, v, m);
}
void NuVecMtxTransformVU0(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float x = m->m[3][0] + (v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0]);
    float y = m->m[3][1] + (v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1]);
    float z = m->m[3][2] + (v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2]);
    out->x = x;
    out->y = y;
    out->z = z;
}
void NuVecInvMtxTransformVU0(NUVEC* out, NUVEC const* v, NUMTX const* m) {
    float dx = v->x - m->m[3][0];
    float dy = v->y - m->m[3][1];
    float dz = v->z - m->m[3][2];
    out->x = dx * m->m[0][0] + dy * m->m[0][1] + dz * m->m[0][2];
    out->y = dx * m->m[1][0] + dy * m->m[1][1] + dz * m->m[1][2];
    out->z = dx * m->m[2][0] + dy * m->m[2][1] + dz * m->m[2][2];
}
void NuVec4MtxRotateVU0(NUVEC4* out, NUVEC4 const* v, NUMTX const* m) {
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0];
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2];
    out->x = x;
    out->y = y;
    out->z = z;
    out->w = v->w;
}
void NuVec4Add(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2) {
    out->w = v1->w + v2->w;
    out->x = v1->x + v2->x;
    out->y = v1->y + v2->y;
    out->z = v1->z + v2->z;
}
void NuVec4Sub(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2) {
    out->x = v1->x - v2->x;
    out->y = v1->y - v2->y;
    out->z = v1->z - v2->z;
    out->w = v1->w - v2->w;
}
void NuVec4Scale(NUVEC4* out, NUVEC4 const* in, float scale) {
    out->x = in->x * scale;
    out->y = in->y * scale;
    out->z = in->z * scale;
    out->w = in->w * scale;
}
void NuVec4AddScale(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2, float scale) {
    out->x = v1->x + v2->x * scale;
    out->y = v1->y + v2->y * scale;
    out->z = v1->z + v2->z * scale;
    out->w = v1->w + v2->w * scale;
}
float NuVec4Dot(NUVEC4 const* v1, NUVEC4 const* v2) {
    return v1->w * v2->w + v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}
void NuVec4Max(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2) {
    out->x = v1->x > v2->x ? v1->x : v2->x;
    out->y = v1->y > v2->y ? v1->y : v2->y;
    out->z = v1->z > v2->z ? v1->z : v2->z;
    out->w = v1->w > v2->w ? v1->w : v2->w;
}
void NuVec4Min(NUVEC4* out, NUVEC4 const* v1, NUVEC4 const* v2) {
    out->x = v1->x < v2->x ? v1->x : v2->x;
    out->y = v1->y < v2->y ? v1->y : v2->y;
    out->z = v1->z < v2->z ? v1->z : v2->z;
    out->w = v1->w < v2->w ? v1->w : v2->w;
}
float NuVec4Mag(NUVEC4 const* v) {
    return NuFsqrt(NuVec4MagSqr(v));
}
float NuVec4MagSqr(NUVEC4 const* v) {
    return v->w * v->w + v->x * v->x + v->y * v->y + v->z * v->z;
}
void NuVec4Lerp(NUVEC4* out, NUVEC4 const* start, NUVEC4 const* end, float t) {
    out->x = end->x + (start->x - end->x) * t;
    out->y = end->y + (start->y - end->y) * t;
    out->z = end->z + (start->z - end->z) * t;
    out->w = end->w + (start->w - end->w) * t;
}
void NuVec4ToNuHalfVec4(NUVEC4 const* in, NUHALFVEC4* out) {
    out->x = NuFloatToHalf(in->x);
    out->y = NuFloatToHalf(in->y);
    out->z = NuFloatToHalf(in->z);
    out->w = NuFloatToHalf(in->w);
}
void NuHalfVec4ToNuVec4(NUHALFVEC4 const* in, NUVEC4* out) {
    out->x = NuHalfToFloat(in->x);
    out->y = NuHalfToFloat(in->y);
    out->z = NuHalfToFloat(in->z);
    out->w = NuHalfToFloat(in->w);
}
float NuVecMagVU0(NUVEC const* v) {
    return NuFsqrt(NuVecDot(v, v));
}
