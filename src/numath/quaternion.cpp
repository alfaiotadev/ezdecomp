#include "numath/quaternion.h"
#include "numath/scalar.h"
#include "numath/types.h"

float NuQuatMagnitude(NUQUAT const* q) {
    return q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
}
float NuQuatDot(NUQUAT const* a, NUQUAT const* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}
void NuQuatNeg2(NUQUAT* out, NUQUAT* in) {
    out->x = -in->x;
    out->y = -in->y;
    out->z = -in->z;
    out->w = -in->w;
}
void NuQuatAdd(NUQUAT* out, NUQUAT const* a, NUQUAT const* b) {
    out->w = a->w + b->w;
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}
void NuQuatSub(NUQUAT* out, NUQUAT const* a, NUQUAT const* b) {
    out->w = a->w - b->w;
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}
void NuQuatScaleAccum(NUQUAT* out, NUQUAT const* in, float scale) {
    out->w += in->w * scale;
    out->x += in->x * scale;
    out->y += in->y * scale;
    out->z += in->z * scale;
}
void NuQuatInv(NUQUAT* out, NUQUAT const* in) {
    float invMag = 1.0f / NuQuatMagnitude(in);
    float x = -(in->x * invMag);
    float y = -(invMag * in->y);
    float z = -(invMag * in->z);
    float w = in->w * invMag;
    out->z = z;
    out->w = w;
    out->x = x;
    out->y = y;
}
void NuQuatHarmonize(NUQUAT const* a, NUQUAT* out) {
    float dot = a->x * out->x + a->y * out->y + a->z * out->z + a->w * out->w;
    if (dot < 0.0f) {
        out->x = -out->x;
        out->y = -out->y;
        out->z = -out->z;
        out->w = -out->w;
    }
}
void NuQuatLerp(NUQUAT* out, NUQUAT const* a, NUQUAT const* b, float t) {
    out->x = (b->x - a->x) * t + a->x;
    out->y = (b->y - a->y) * t + a->y;
    out->z = (b->z - a->z) * t + a->z;
    out->w = (b->w - a->w) * t + a->w;
}
void NuQuatBlend(NUQUAT* out, NUQUAT const* a, NUQUAT const* b, float t1, float t2) {
    out->x = a->x * t1 + b->x * t2;
    out->y = a->y * t1 + b->y * t2;
    out->z = a->z * t1 + b->z * t2;
    out->w = a->w * t1 + b->w * t2;
}
void NuQuatMul(NUQUAT* out, NUQUAT const* a, NUQUAT const* b) {
    float w = b->w * a->w - b->x * a->x - b->y * a->y - b->z * a->z;
    float x = b->w * a->x + a->w * b->x + b->y * a->z - a->y * b->z;
    float y = a->w * b->y + b->w * a->y + a->x * b->z - b->x * a->z;
    float z = a->w * b->z + b->w * a->z + b->x * a->y - a->x * b->y;

    out->x = x;
    out->y = y;
    out->z = z;
    out->w = w;
}
void NuQuatToMtx(NUQUAT const* q, NUMTX* out) {
    float w = q->w;
    float x = q->x;
    float y = q->y;
    float z = q->z;
    float ww = w * w;
    float yy = y * y;
    float xy = x * y;
    float wz = w * z;
    float xx = x * x;
    float zz = z * z;
    float xz = x * z;
    float wx = w * x;
    float yz = y * z;
    float wy = w * y;
    out->m[2][3] = 0.0f;
    out->m[3][3] = 1.0f;
    out->m[3][0] = out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[0][1] = (xy + xy) + (wz + wz);
    out->m[2][0] = (wy + wy) + (xz + xz);
    out->m[2][1] = (yz + yz) - (wx + wx);
    out->m[0][2] = (xz + xz) - (wy + wy);
    out->m[1][0] = (xy + xy) - (wz + wz);
    out->m[1][2] = (wx + wx) + (yz + yz);
    out->m[0][0] = ((ww + xx) - yy) - zz;
    out->m[1][1] = ((ww - xx) + yy) - zz;
    out->m[2][2] = ((ww - xx) - yy) + zz;
}
void NuQuatNormalise(NUQUAT* out, NUQUAT const* in) {
    float magSqr = NuQuatMagnitude(in);
    if (magSqr > 0.0f) {
        float mag = NuFsqrt(magSqr);
        float invMag = mag != 0.0f ? 1.0f / mag : 0.0f;
        float w = in->w * invMag;
        float x = invMag * in->x;
        float z = invMag * in->z;
        float y = invMag * in->y;
        out->x = x;
        out->y = y;
        out->z = z;
        out->w = w;
    } else {
        *out = *in;
    }
}
void NuQuatFromEulerXYZ(NUQUAT* out, int x, int y, int z) {
    float hx = (float)(x / 2) * 9.58738019107841e-05f;
    float hy = (float)(y / 2) * 9.58738019107841e-05f;
    float hz = (float)(z / 2) * 9.58738019107841e-05f;
    float sn[3];
    float cs[3];
    NuSinCos(hx, &sn[0], &cs[0]);
    NuSinCos(hy, &sn[1], &cs[1]);
    NuSinCos(hz, &sn[2], &cs[2]);
    float cc = cs[2] * cs[1];
    float ss = sn[2] * sn[1];
    float sd = cs[2] * sn[1];
    float sc = cs[1] * sn[2];
    float t1 = ss * cs[0];
    float t2 = cc * sn[0];
    float t6 = cc * cs[0];
    out->x = t2 - t1;
    float t3 = sd * cs[0];
    float t4 = sc * cs[0];
    float t7 = sd * sn[0];
    out->z = t4 - t7;
    float t5 = sc * sn[0];
    out->y = t3 + t5;
    float t8 = ss * sn[0];
    out->w = t6 + t8;
}
void NuQuatFromEulerRadsXYZ(NUQUAT* out, float x, float y, float z) {
    float hx = x * 0.5f;
    float hy = y * 0.5f;
    float hz = z * 0.5f;
    float cx, cy, cz;
    float sx, sy, sz;
    NuSinCos(hx, &sx, &cx);
    NuSinCos(hy, &sy, &cy);
    NuSinCos(hz, &sz, &cz);
    float cc = cz * cy;
    float ss = sz * sy;
    float cs = cz * sy;
    float sc = cy * sz;
    float t1 = ss * cx;
    float t2 = cc * sx;
    float t3 = cs * cx;
    float t4 = sc * cx;
    float t5 = sc * sx;
    float t6 = cc * cx;
    float t7 = cs * sx;
    float t8 = ss * sx;
    out->x = t2 - t1;
    out->y = t3 + t5;
    out->z = t4 - t7;
    out->w = t6 + t8;
}
void NuQuatFromEulerVecRads(NUQUAT& out, NUVEC const& v) {
    float hx = v.x * 0.5f;
    float hy = v.y * 0.5f;
    float hz = v.z * 0.5f;
    float cx, cy, cz;
    float sx, sy, sz;
    NuSinCos(hx, &sx, &cx);
    NuSinCos(hy, &sy, &cy);
    NuSinCos(hz, &sz, &cz);
    float cc = cz * cy;
    float ss = sz * sy;
    float cs = cz * sy;
    float sc = cy * sz;
    float t1 = ss * cx;
    float t2 = cc * sx;
    float t3 = cs * cx;
    float t4 = sc * cx;
    float t5 = sc * sx;
    float t6 = cc * cx;
    float t7 = cs * sx;
    float t8 = ss * sx;
    out.x = t2 - t1;
    out.y = t3 + t5;
    out.z = t4 - t7;
    out.w = t6 + t8;
}
void NuMtxToQuat(NUMTX const* mtx, NUQUAT* out) {
    static const int nxt[3] = {1, 2, 0};
    float tr = mtx->m[0][0] + mtx->m[1][1] + mtx->m[2][2];
    if (tr > 0.0f) {
        float s = NuFsqrt(tr + 1.0f);
        out->w = s * 0.5f;
        s = 0.5f / s;
        out->x = (mtx->m[1][2] - mtx->m[2][1]) * s;
        out->y = (mtx->m[2][0] - mtx->m[0][2]) * s;
        out->z = (mtx->m[0][1] - mtx->m[1][0]) * s;
    } else {
        const float* mf = &mtx->m[0][0];
        int i = 0;
        if (mtx->m[1][1] > mtx->m[0][0])
            i = 1;
        if (mtx->m[2][2] > mf[i * 4 + i])
            i = 2;
        int j = nxt[i];
        int k = nxt[j];
        float s = NuFsqrt(mf[i * 4 + i] - (mf[(j << 2) + j] + mf[(k << 2) + k]) + 1.0f);
        float q[4];
        q[i] = s * 0.5f;
        s = s != 0.0f ? 0.5f / s : s;
        q[3] = (mf[(j << 2) + k] - mf[(k << 2) + j]) * s;
        q[j] = (mf[i * 4 + j] + mf[(j << 2) + i]) * s;
        q[k] = (mf[i * 4 + k] + mf[(k << 2) + i]) * s;
        out->x = q[0];
        out->y = q[1];
        out->z = q[2];
        out->w = q[3];
    }
}
void NuMtxToQuatRH(NUMTX const* mtx, NUQUAT* out) {
    static const int nxt[3] = {1, 2, 0};
    float tr = mtx->m[0][0] + mtx->m[1][1];
    float d22 = mtx->m[2][2];
    tr = tr + d22;
    if (tr > 0.0f) {
        float s = NuFsqrt(tr + 1.0f);
        out->w = s * 0.5f;
        s = 0.5f / s;
        out->x = (mtx->m[2][1] - mtx->m[1][2]) * s;
        out->y = (mtx->m[0][2] - mtx->m[2][0]) * s;
        out->z = (mtx->m[0][1] - mtx->m[1][0]) * s;
    } else {
        const float* mf = &mtx->m[0][0];
        int i = 0;
        if (mtx->m[1][1] > mtx->m[0][0])
            i = 1;
        float diag = mf[i * 4 + i];
        if (d22 > diag)
            i = 2;
        int j = nxt[i];
        int k = nxt[j];
        float s = NuFsqrt(mf[i * 4 + i] - (mf[(j << 2) + j] + mf[(k << 2) + k]) + 1.0f);
        float q[4];
        q[i] = s * 0.5f;
        s = s != 0.0f ? 0.5f / s : s;
        if (d22 > diag)
            q[3] = (mf[(j << 2) + k] - mf[(k << 2) + j]) * s;
        else
            q[3] = (mf[(k << 2) + j] - mf[(j << 2) + k]) * s;
        q[j] = (mf[i * 4 + j] + mf[(j << 2) + i]) * s;
        q[k] = (mf[i * 4 + k] + mf[(k << 2) + i]) * s;
        out->x = q[0];
        out->y = q[1];
        out->z = q[2];
        out->w = q[3];
    }
}
void NuEulerVecFromQuatRads(NUQUAT const& q, NUVEC& out) {
    float sp = -2.0f * (q.x * q.z - q.w * q.y);
    sp = sp < -1.0f ? -1.0f : sp;
    sp = sp > 1.0f ? 1.0f : sp;
    out.x = NuATan2f(2.0f * (q.z * q.y + q.x * q.w), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);
    out.y = NuASinf(sp);
    out.z = NuATan2f(2.0f * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z);
}
void NuEulerXYZFromQuat(int* x, int* y, int* z, NUQUAT const* q) {
    float qx = q->x;
    float qy = q->y;
    float qz = q->z;
    float qw = q->w;
    float sp = -2.0f * (qx * qz - qy * qw);
    sp = sp < -1.0f ? -1.0f : sp;
    sp = sp > 1.0f ? 1.0f : sp;
    *y = (short)NuASinOld(sp);
    *x = (int)(NuATan2f(2.0f * (qy * qz + qx * qw), qw * qw - qx * qx - qy * qy + qz * qz)
               * 10430.3779296875f);
    *z = (int)(NuATan2f(2.0f * (qx * qy + qz * qw), qx * qx + qw * qw - qy * qy - qz * qz)
               * 10430.3779296875f);
}
void NuQuatSlerp(NUQUAT* out, NUQUAT const* a, NUQUAT const* b, float t) {
    float dot = a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
    float bx = b->x;
    float by = b->y;
    float bz = b->z;
    float bw = b->w;
    if (dot < 0.0f) {
        dot = -dot;
        bx = -bx;
        by = -by;
        bz = -bz;
        bw = -bw;
    }
    float scale0 = 0.0f;
    float scale1 = t;
    if (1.0f - dot > 1.0e-5f) {
        int theta = (short)(16384 - NuASinOld(dot));
        float thetaF = (float)theta;
        float sinTheta = NuSinOld(theta);
        float s0 = NuSinOld((int)((1.0f - t) * thetaF));
        if (sinTheta * s0 != 0.0f)
            scale0 = s0 / sinTheta;
        float s1 = NuSinOld((int)(thetaF * t));
        scale1 = 0.0f;
        if (sinTheta * s1 != 0.0f)
            scale1 = s1 / sinTheta;
    } else {
        scale0 = 1.0f - t;
    }
    float ax = a->x;
    float ay = a->y;
    float az = a->z;
    float aw = a->w;
    out->x = bx * scale1 + scale0 * ax;
    out->y = by * scale1 + scale0 * ay;
    out->z = bz * scale1 + scale0 * az;
    out->w = bw * scale1 + scale0 * aw;
}
void NuQuatHermiteInt(NUQUAT* out, NUQUAT* a, NUQUAT* b, NUQUAT* c, NUQUAT* d, float t) {
    NuQuatHarmonize(a, b);
    NuQuatHarmonize(b, c);
    NuQuatHarmonize(c, d);

    float cx = c->x, cy = c->y, cz = c->z, cw = c->w;
    float dx = d->x, dy = d->y, dz = d->z, dw = d->w;

    float t2 = t * t;
    float t3 = t2 * t;
    float h00b = 2.0f * t3 - 3.0f * t2;
    float h01 = 3.0f * t2 - 2.0f * t3;
    float h00 = h00b + 1.0f;
    float h11 = t3 - t2;
    float h10 = t3 - 2.0f * t2 + t;

    out->x = h11 * ((dx - b->x) * 0.5f) + ((h00 * b->x + h10 * ((cx - a->x) * 0.5f)) + h01 * cx);
    out->y = h11 * ((dy - b->y) * 0.5f) + ((h00 * b->y + h10 * ((cy - a->y) * 0.5f)) + h01 * cy);
    out->z = h11 * ((dz - b->z) * 0.5f) + ((h00 * b->z + h10 * ((cz - a->z) * 0.5f)) + h01 * cz);
    out->w = h11 * ((dw - b->w) * 0.5f) + ((h00 * b->w + h10 * ((cw - a->w) * 0.5f)) + h01 * cw);
}
void NuQuatCubicInt(NUQUAT* out, NUQUAT* a, NUQUAT* b, NUQUAT* c, NUQUAT* d, float t) {
    NuQuatHarmonize(a, b);
    NuQuatHarmonize(b, c);
    NuQuatHarmonize(c, d);

    float cx = c->x, cy = c->y, cz = c->z, cw = c->w;
    float dx = d->x, dy = d->y, dz = d->z, dw = d->w;

    float A3x = ((b->x * 0.5f - a->x / 6.0f) - cx * 0.5f) + dx / 6.0f;
    float A2x = cx * 0.5f + (a->x * 0.5f - b->x);
    float A1x = (cx + (-a->x / 3.0f - b->x * 0.5f)) - dx / 6.0f;
    out->x = b->x + (A1x * t + (t * t * A2x + t * t * t * A3x));

    float A3y = ((b->y * 0.5f - a->y / 6.0f) - cy * 0.5f) + dy / 6.0f;
    float A2y = cy * 0.5f + (a->y * 0.5f - b->y);
    float A1y = (cy + (-a->y / 3.0f - b->y * 0.5f)) - dy / 6.0f;
    out->y = b->y + (A1y * t + (t * t * A2y + t * t * t * A3y));

    float A3z = ((b->z * 0.5f - a->z / 6.0f) - cz * 0.5f) + dz / 6.0f;
    float A2z = cz * 0.5f + (a->z * 0.5f - b->z);
    float A1z = (cz + (-a->z / 3.0f - b->z * 0.5f)) - dz / 6.0f;
    out->z = b->z + (A1z * t + (t * t * A2z + t * t * t * A3z));

    float A3w = ((b->w * 0.5f - a->w / 6.0f) - cw * 0.5f) + dw / 6.0f;
    float A2w = cw * 0.5f + (a->w * 0.5f - b->w);
    float A1w = (cw + (-a->w / 3.0f - b->w * 0.5f)) - dw / 6.0f;
    out->w = b->w + (A1w * t + (t * t * A2w + t * t * t * A3w));
}
