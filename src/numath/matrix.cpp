#include "numath/matrix.h"
#include "numath/scalar.h"
#include "numath/types.h"
#include "numath/vector.h"

NUMTX numtx_zero;
NUMTX numtx_identity = {{
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
}};

void NuMtxSetZero(NUMTX* out) {
    *out = numtx_zero;
}
void NuMtxSetIdentity(NUMTX* out) {
    *out = numtx_identity;
}
void NuMtxSetTranslation(NUMTX* out, NUVEC const* translation) {
    out->m[3][0] = translation->x;
    out->m[3][1] = translation->y;
    out->m[3][2] = translation->z;
    out->m[3][3] = 1.0f;
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[2][2] = 1.0f;
    out->m[1][1] = 1.0f;
    out->m[0][0] = 1.0f;
}
void NuMtxSetTranslationNeg(NUMTX* out, NUVEC const* translation) {
    out->m[3][0] = -translation->x;
    out->m[3][1] = -translation->y;
    out->m[3][2] = -translation->z;
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[2][2] = 1.0f;
    out->m[3][3] = 1.0f;
    out->m[1][1] = 1.0f;
    out->m[0][0] = 1.0f;
}
void NuMtxSetScale(NUMTX* out, NUVEC const* scale) {
    out->m[0][0] = scale->x;
    out->m[1][1] = scale->y;
    out->m[2][2] = scale->z;
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}

void NuMtxSetRotationXOld(NUMTX* out, int angle) {
    float c = NuSinOld(angle + 16384);
    out->m[2][2] = c;
    out->m[1][1] = c;
    float s = NuSinOld(angle);
    out->m[1][2] = s;
    out->m[2][1] = -s;
    out->m[0][0] = 1.0f;
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[3][3] = 1.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
}
void NuMtxSetRotationYOld(NUMTX* out, int angle) {
    float c = NuSinOld(angle + 16384);
    out->m[2][2] = c;
    out->m[0][0] = c;
    float s = NuSinOld(angle);
    out->m[2][0] = s;
    out->m[1][3] = 0.0f;
    out->m[1][2] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = 1.0f;
    out->m[0][3] = 0.0f;
    out->m[0][1] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[0][2] = -s;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotationZOld(NUMTX* out, int angle) {
    float c = NuSinOld(angle + 16384);
    out->m[1][1] = c;
    out->m[0][0] = c;
    float s = NuSinOld(angle);
    out->m[0][1] = s;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[2][2] = 1.0f;
    out->m[1][0] = -s;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotationXRads(NUMTX* out, float rads) {
    float c = NuCosf(rads);
    out->m[2][2] = c;
    out->m[1][1] = c;
    float s = NuSinf(rads);
    out->m[1][2] = s;
    out->m[2][1] = -s;
    out->m[0][0] = 1.0f;
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[3][3] = 1.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
}
void NuMtxSetRotationYRads(NUMTX* out, float rads) {
    float c = NuCosf(rads);
    out->m[2][2] = c;
    out->m[0][0] = c;
    float s = NuSinf(rads);
    out->m[2][0] = s;
    out->m[1][3] = 0.0f;
    out->m[1][2] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = 1.0f;
    out->m[0][3] = 0.0f;
    out->m[0][1] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[0][2] = -s;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotationZRads(NUMTX* out, float rads) {
    float c = NuCosf(rads);
    out->m[1][1] = c;
    out->m[0][0] = c;
    float s = NuSinf(rads);
    out->m[0][1] = s;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[2][2] = 1.0f;
    out->m[1][0] = -s;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotateXYZRads(NUMTX* out, NUVEC const* rads) {
    float cx = NuCosf(rads->x);
    float sx = NuSinf(rads->x);
    float cy = NuCosf(rads->y);
    float sy = NuSinf(rads->y);
    float cz = NuCosf(rads->z);
    float sz = NuSinf(rads->z);
    out->m[0][0] = cy * cz;
    out->m[0][1] = cy * sz;
    out->m[0][2] = -sy;
    out->m[0][3] = 0.0f;
    out->m[1][0] = sx * sy * cz - cx * sz;
    out->m[1][1] = cx * cz + sx * sy * sz;
    out->m[1][2] = sx * cy;
    out->m[1][3] = 0.0f;
    out->m[2][0] = cx * sy * cz + sx * sz;
    out->m[2][1] = cx * sy * sz - sx * cz;
    out->m[2][2] = cx * cy;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotateYXZRads(NUMTX* out, NUVEC const* rads) {
    float cx = NuCosf(rads->x);
    float sx = NuSinf(rads->x);
    float cy = NuCosf(rads->y);
    float sy = NuSinf(rads->y);
    float cz = NuCosf(rads->z);
    float sz = NuSinf(rads->z);
    out->m[0][0] = cy * cz - sx * sy * sz;
    out->m[0][1] = sx * sy * cz + cy * sz;
    out->m[0][2] = -cx * sy;
    out->m[0][3] = 0.0f;
    out->m[1][0] = -cx * sz;
    out->m[1][1] = cx * cz;
    out->m[1][2] = sx;
    out->m[1][3] = 0.0f;
    out->m[2][0] = sy * cz + sx * cy * sz;
    out->m[2][1] = sy * sz - sx * cy * cz;
    out->m[2][2] = cx * cy;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotateXYZOld(NUMTX* out, NUANGVEC const* angles) {
    float cx = NuSinOld(angles->x + 16384);
    float sx = NuSinOld(angles->x);
    float cy = NuSinOld(angles->y + 16384);
    float sy = NuSinOld(angles->y);
    float cz = NuSinOld(angles->z + 16384);
    float sz = NuSinOld(angles->z);
    out->m[0][0] = cy * cz;
    out->m[0][1] = cy * sz;
    out->m[0][2] = -sy;
    out->m[0][3] = 0.0f;
    out->m[1][0] = sx * sy * cz - cx * sz;
    out->m[1][1] = cx * cz + sx * sy * sz;
    out->m[1][2] = sx * cy;
    out->m[1][3] = 0.0f;
    out->m[2][0] = cx * sy * cz + sx * sz;
    out->m[2][1] = cx * sy * sz - sx * cz;
    out->m[2][2] = cx * cy;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotateYXZOld(NUMTX* out, NUANGVEC const* angles) {
    float cx = NuSinOld(angles->x + 16384);
    float sx = NuSinOld(angles->x);
    float cy = NuSinOld(angles->y + 16384);
    float sy = NuSinOld(angles->y);
    float cz = NuSinOld(angles->z + 16384);
    float sz = NuSinOld(angles->z);
    out->m[0][0] = cy * cz - sx * sy * sz;
    out->m[0][1] = sx * sy * cz + cy * sz;
    out->m[0][2] = -cx * sy;
    out->m[0][3] = 0.0f;
    out->m[1][0] = -cx * sz;
    out->m[1][1] = cx * cz;
    out->m[1][2] = sx;
    out->m[1][3] = 0.0f;
    out->m[2][0] = sy * cz + sx * cy * sz;
    out->m[2][1] = sy * sz - sx * cy * cz;
    out->m[2][2] = cx * cy;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotationAxisRads(NUMTX* out, float rads, NUVEC const* axis) {
    float half = rads * 0.5f;
    float s = NuSinf(half);
    float w = NuCosf(half);
    float x = s * axis->x;
    float y = s * axis->y;
    float z = s * axis->z;
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float wx2 = w * x2;
    float wy2 = w * y2;
    float wz2 = w * z2;
    float xx2 = x * x2;
    float xy2 = x * y2;
    float xz2 = x * z2;
    float yy2 = y * y2;
    float yz2 = y * z2;
    float zz2 = z * z2;
    out->m[0][0] = 1.0f - (yy2 + zz2);
    out->m[0][1] = xy2 + wz2;
    out->m[0][2] = xz2 - wy2;
    out->m[0][3] = 0.0f;
    out->m[1][0] = xy2 - wz2;
    out->m[1][1] = 1.0f - (xx2 + zz2);
    out->m[1][2] = wx2 + yz2;
    out->m[1][3] = 0.0f;
    out->m[2][0] = wy2 + xz2;
    out->m[2][1] = yz2 - wx2;
    out->m[2][2] = 1.0f - (xx2 + yy2);
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetRotationAxisOld(NUMTX* out, int angle, NUVEC const* axis) {
    int half = angle >> 1;
    float s = NuSinOld(half);
    float w = NuSinOld(half + 16384);
    float x = s * axis->x;
    float y = s * axis->y;
    float z = s * axis->z;
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float wx2 = w * x2;
    float wy2 = w * y2;
    float wz2 = w * z2;
    float xx2 = x * x2;
    float xy2 = x * y2;
    float xz2 = x * z2;
    float yy2 = y * y2;
    float yz2 = y * z2;
    float zz2 = z * z2;
    out->m[0][0] = 1.0f - (yy2 + zz2);
    out->m[0][1] = xy2 + wz2;
    out->m[0][2] = xz2 - wy2;
    out->m[0][3] = 0.0f;
    out->m[1][0] = xy2 - wz2;
    out->m[1][1] = 1.0f - (xx2 + zz2);
    out->m[1][2] = wx2 + yz2;
    out->m[1][3] = 0.0f;
    out->m[2][0] = wy2 + xz2;
    out->m[2][1] = yz2 - wx2;
    out->m[2][2] = 1.0f - (xx2 + yy2);
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSetPerspectiveD3DWH(NUMTX* out, float width, float height, float zNear, float zFar) {
    float n2 = zNear + zNear;
    out->m[0][0] = n2 / width;
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = n2 / height;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][2] = zFar / (zFar - zNear);
    out->m[2][3] = 1.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = -(zNear * zFar) / (zFar - zNear);
    out->m[3][3] = 0.0f;
}
void NuMtxSetPerspectiveD3D(NUMTX* out, float fovY, float aspect, float zNear, float zFar) {
    int angle = (int)(fovY * 0.5f * (65536.0f / 360.0f));
    float t = NuSinOld(angle) / NuSinOld(angle + 16384);
    out->m[0][0] = 1.0f / (t * aspect);
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = 1.0f / t;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][2] = zFar / (zFar - zNear);
    out->m[2][3] = 1.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = -(zNear * zFar) / (zFar - zNear);
    out->m[3][3] = 0.0f;
}
void NuMtxSetPerspectiveBlend(NUMTX* out, float fovY, float aspect, float zNear, float zFar) {
    int angle = (int)(fovY * 0.5f * (65536.0f / 360.0f));
    float t = NuSinOld(angle) / NuSinOld(angle + 16384);
    out->m[0][0] = 1.0f / (t * aspect);
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = 1.0f / t;
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][2] = (zNear + zFar) / (zFar - zNear);
    out->m[2][3] = 1.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = zFar * -2.0f * zNear / (zFar - zNear);
    out->m[3][3] = 0.0f;
}
void NuMtxSetFrustumD3D(NUMTX* out, float l, float r, float b, float t, float n, float f) {
    float n2 = n + n;
    out->m[0][0] = n2 / (r - l);
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = n2 / (t - b);
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = (l + r) / (l - r);
    out->m[2][1] = (b + t) / (b - t);
    out->m[2][2] = f / (f - n);
    out->m[2][3] = 1.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = -(n * f) / (f - n);
    out->m[3][3] = 0.0f;
}
void NuMtxSetOrthoD3D(NUMTX* out, float l, float r, float b, float t, float n, float f) {
    out->m[0][0] = 2.0f / (r - l);
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = 2.0f / (t - b);
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][2] = 1.0f / (f - n);
    out->m[2][3] = 0.0f;
    out->m[3][0] = (l + r) / (l - r);
    out->m[3][1] = (b + t) / (b - t);
    out->m[3][2] = -n / (f - n);
    out->m[3][3] = 1.0f;
}
void NuMtxSetFrustumBlend(NUMTX* out, float l, float r, float b, float t, float n, float f) {
    float n2 = n + n;
    out->m[0][0] = n2 / (r - l);
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = n2 / (t - b);
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = (l + r) / (l - r);
    out->m[2][1] = (b + t) / (b - t);
    out->m[2][2] = (n + f) / (f - n);
    out->m[2][3] = 1.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = f * -2.0f * n / (f - n);
    out->m[3][3] = 0.0f;
}
void NuMtxSetOrthoBlend(NUMTX* out, float l, float r, float b, float t, float n, float f) {
    out->m[0][0] = 2.0f / (r - l);
    out->m[0][1] = 0.0f;
    out->m[0][2] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;
    out->m[1][1] = 2.0f / (t - b);
    out->m[1][2] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;
    out->m[2][1] = 0.0f;
    out->m[2][2] = 2.0f / (f - n);
    out->m[2][3] = 0.0f;
    out->m[3][0] = (l + r) / (l - r);
    out->m[3][1] = (b + t) / (b - t);
    out->m[3][2] = (n + f) / (n - f);
    out->m[3][3] = 1.0f;
}
bool NuMtxGetHandiness(NUMTX const* mtx) {
    NUVEC x;
    NUVEC y;
    NUVEC z;
    NuMtxGetXAxis(mtx, &x);
    NuMtxGetYAxis(mtx, &y);
    NuMtxGetZAxis(mtx, &z);
    NUVEC cross;
    NuVecCross(&cross, &x, &y);
    return NuVecDot(&z, &cross) > 0.0f;
}
void NuMtxGetXAxis(NUMTX const* mtx, NUVEC* out) {
    out->x = mtx->m[0][0];
    out->y = mtx->m[0][1];
    out->z = mtx->m[0][2];
}
void NuMtxGetYAxis(NUMTX const* mtx, NUVEC* out) {
    out->x = mtx->m[1][0];
    out->y = mtx->m[1][1];
    out->z = mtx->m[1][2];
}
void NuMtxGetZAxis(NUMTX const* mtx, NUVEC* out) {
    out->x = mtx->m[2][0];
    out->y = mtx->m[2][1];
    out->z = mtx->m[2][2];
}
void NuMtxGetTranslation(NUMTX const* mtx, NUVEC* out) {
    out->x = mtx->m[3][0];
    out->y = mtx->m[3][1];
    out->z = mtx->m[3][2];
}
NUVEC NuMtxGetScale(NUMTX const* mtx) {
    NUVEC scale;
    scale.x
        = NuFsqrt(mtx->m[0][0] * mtx->m[0][0] + mtx->m[0][1] * mtx->m[0][1] + mtx->m[0][2] * mtx->m[0][2]);
    scale.y
        = NuFsqrt(mtx->m[1][0] * mtx->m[1][0] + mtx->m[1][1] * mtx->m[1][1] + mtx->m[1][2] * mtx->m[1][2]);
    scale.z
        = NuFsqrt(mtx->m[2][0] * mtx->m[2][0] + mtx->m[2][1] * mtx->m[2][1] + mtx->m[2][2] * mtx->m[2][2]);
    return scale;
}
void NuMtxGetEulerAngVecRads(NUMTX const& mtx, NUVEC& outAngVec) {
    NuMtxGetEulerXYZRads(&mtx, &outAngVec.x, &outAngVec.y, &outAngVec.z);
}
void NuMtxGetPerspectiveD3D(NUMTX const* mtx, float* fovY, float* aspect, float* zNear, float* zFar) {
    float d = mtx->m[2][2];
    float zn = -mtx->m[3][2] / d;
    *zNear = zn;
    *zFar = d * zn / (d - 1.0f);
    *aspect = mtx->m[1][1] / mtx->m[0][0];
    *fovY = NuATan2f(1.0f / mtx->m[1][1], 1.0f) * 360.0f / 3.1415927f;
}
void NuMtxGetPerspectiveBlend(NUMTX const* mtx, float* fovY, float* aspect, float* zNear, float* zFar) {
    float a = (mtx->m[2][2] + 1.0f) * 0.5f;
    float zn = mtx->m[3][2] * -0.5f / a;
    *zNear = zn;
    *zFar = a * zn / (a - 1.0f);
    *aspect = mtx->m[1][1] / mtx->m[0][0];
    *fovY = NuATan2f(1.0f / mtx->m[1][1], 1.0f) * 360.0f / 3.1415927f;
}
void NuMtxGetFrustumD3D(NUMTX const* mtx, float* l, float* r, float* b, float* t, float* n, float* f) {
    float d = mtx->m[2][2];
    float prod = d * mtx->m[3][2];
    float zn = mtx->m[3][2] / d;
    zn = -(prod == 0.0f ? 0.0f : zn);
    if (f) {
        *f = d * ((d - 1.0f) * zn == 0.0f ? 0.0f : zn / (d - 1.0f));
    }
    if (l) {
        *l = (-1.0f - mtx->m[2][0]) * (zn * mtx->m[0][0] == 0.0f ? 0.0f : zn / mtx->m[0][0]);
    }
    if (r) {
        *r = (1.0f - mtx->m[2][0]) * (zn * mtx->m[0][0] == 0.0f ? 0.0f : zn / mtx->m[0][0]);
    }
    if (b) {
        *b = (-1.0f - mtx->m[2][1]) * (zn * mtx->m[1][1] == 0.0f ? 0.0f : zn / mtx->m[1][1]);
    }
    if (t) {
        *t = (1.0f - mtx->m[2][1]) * (zn * mtx->m[1][1] == 0.0f ? 0.0f : zn / mtx->m[1][1]);
    }
    if (n) {
        *n = zn;
    }
}
void NuMtxGetFrustumBlend(NUMTX const* mtx, float* l, float* r, float* b, float* t, float* n, float* f) {
    float a = (mtx->m[2][2] + 1.0f) * 0.5f;
    float zn = mtx->m[3][2] * -0.5f / a;
    if (f) {
        *f = a * zn / (a - 1.0f);
    }
    if (l) {
        *l = zn * (-1.0f - mtx->m[2][0]) / mtx->m[0][0];
    }
    if (r) {
        *r = zn * (1.0f - mtx->m[2][0]) / mtx->m[0][0];
    }
    if (b) {
        *b = zn * (-1.0f - mtx->m[2][1]) / mtx->m[1][1];
    }
    if (t) {
        *t = zn * (1.0f - mtx->m[2][1]) / mtx->m[1][1];
    }
    if (n) {
        *n = zn;
    }
}
void NuMtxGetOrthoD3D(NUMTX const* mtx, float* l, float* r, float* b, float* t, float* n, float* f) {
    *r = (1.0f - mtx->m[3][0]) / mtx->m[0][0];
    *l = -(mtx->m[3][0] + 1.0f) / mtx->m[0][0];
    *t = (1.0f - mtx->m[3][1]) / mtx->m[1][1];
    *b = -(mtx->m[3][1] + 1.0f) / mtx->m[1][1];
    *n = -mtx->m[3][2] / mtx->m[2][2];
    *f = (1.0f - mtx->m[3][2]) / mtx->m[2][2];
}
void NuMtxTranslate(NUMTX* mtx, NUVEC const* translation) {
    mtx->m[3][0] = translation->x + mtx->m[3][0];
    mtx->m[3][1] = translation->y + mtx->m[3][1];
    mtx->m[3][2] = translation->z + mtx->m[3][2];
}
void NuMtxTranslateNeg(NUMTX* mtx, NUVEC const* translation) {
    mtx->m[3][0] -= translation->x;
    mtx->m[3][1] -= translation->y;
    mtx->m[3][2] -= translation->z;
}
void NuMtxRotateXRads(NUMTX* mtx, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float a0 = mtx->m[0][1], b0 = mtx->m[0][2];
    float a1 = mtx->m[1][1], b1 = mtx->m[1][2];
    float a2 = mtx->m[2][1], b2 = mtx->m[2][2];
    mtx->m[0][1] = c * a0 - s * b0;
    mtx->m[0][2] = s * a0 + c * b0;
    mtx->m[1][1] = c * a1 - s * b1;
    mtx->m[1][2] = s * a1 + c * b1;
    mtx->m[2][1] = c * a2 - s * b2;
    mtx->m[2][2] = s * a2 + c * b2;
    float a3 = mtx->m[3][1], b3 = mtx->m[3][2];
    mtx->m[3][1] = c * a3 - s * b3;
    mtx->m[3][2] = s * a3 + c * b3;
}
void NuMtxRotateYRads(NUMTX* mtx, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float a0 = mtx->m[0][0], b0 = mtx->m[0][2];
    float a1 = mtx->m[1][0], b1 = mtx->m[1][2];
    float a2 = mtx->m[2][0], b2 = mtx->m[2][2];
    mtx->m[0][0] = c * a0 + s * b0;
    mtx->m[0][2] = c * b0 - s * a0;
    mtx->m[1][0] = c * a1 + s * b1;
    mtx->m[1][2] = c * b1 - s * a1;
    mtx->m[2][0] = c * a2 + s * b2;
    mtx->m[2][2] = c * b2 - s * a2;
    float a3 = mtx->m[3][0], b3 = mtx->m[3][2];
    mtx->m[3][0] = c * a3 + s * b3;
    mtx->m[3][2] = c * b3 - s * a3;
}
void NuMtxRotateZRads(NUMTX* mtx, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float a0 = mtx->m[0][0], b0 = mtx->m[0][1];
    float a1 = mtx->m[1][0], b1 = mtx->m[1][1];
    float a2 = mtx->m[2][0], b2 = mtx->m[2][1];
    mtx->m[0][0] = c * a0 - s * b0;
    mtx->m[0][1] = s * a0 + c * b0;
    mtx->m[1][0] = c * a1 - s * b1;
    mtx->m[1][1] = s * a1 + c * b1;
    mtx->m[2][0] = c * a2 - s * b2;
    mtx->m[2][1] = s * a2 + c * b2;
    float a3 = mtx->m[3][0], b3 = mtx->m[3][1];
    mtx->m[3][0] = c * a3 - s * b3;
    mtx->m[3][1] = s * a3 + c * b3;
}
void NuMtxRotateXOld(NUMTX* mtx, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float a0 = mtx->m[0][1], b0 = mtx->m[0][2];
    float a1 = mtx->m[1][1], b1 = mtx->m[1][2];
    float a2 = mtx->m[2][1], b2 = mtx->m[2][2];
    mtx->m[0][1] = c * a0 - s * b0;
    mtx->m[0][2] = s * a0 + c * b0;
    mtx->m[1][1] = c * a1 - s * b1;
    mtx->m[1][2] = s * a1 + c * b1;
    mtx->m[2][1] = c * a2 - s * b2;
    mtx->m[2][2] = s * a2 + c * b2;
    float a3 = mtx->m[3][1], b3 = mtx->m[3][2];
    mtx->m[3][1] = c * a3 - s * b3;
    mtx->m[3][2] = s * a3 + c * b3;
}
void NuMtxRotateYOld(NUMTX* mtx, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float a0 = mtx->m[0][0], b0 = mtx->m[0][2];
    float a1 = mtx->m[1][0], b1 = mtx->m[1][2];
    float a2 = mtx->m[2][0], b2 = mtx->m[2][2];
    mtx->m[0][0] = c * a0 + s * b0;
    mtx->m[0][2] = c * b0 - s * a0;
    mtx->m[1][0] = c * a1 + s * b1;
    mtx->m[1][2] = c * b1 - s * a1;
    mtx->m[2][0] = c * a2 + s * b2;
    mtx->m[2][2] = c * b2 - s * a2;
    float a3 = mtx->m[3][0], b3 = mtx->m[3][2];
    mtx->m[3][0] = c * a3 + s * b3;
    mtx->m[3][2] = c * b3 - s * a3;
}
void NuMtxRotateZOld(NUMTX* mtx, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float a0 = mtx->m[0][0], b0 = mtx->m[0][1];
    float a1 = mtx->m[1][0], b1 = mtx->m[1][1];
    float a2 = mtx->m[2][0], b2 = mtx->m[2][1];
    mtx->m[0][0] = c * a0 - s * b0;
    mtx->m[0][1] = s * a0 + c * b0;
    mtx->m[1][0] = c * a1 - s * b1;
    mtx->m[1][1] = s * a1 + c * b1;
    mtx->m[2][0] = c * a2 - s * b2;
    mtx->m[2][1] = s * a2 + c * b2;
    float a3 = mtx->m[3][0], b3 = mtx->m[3][1];
    mtx->m[3][0] = c * a3 - s * b3;
    mtx->m[3][1] = s * a3 + c * b3;
}
void NuMtxScale(NUMTX* mtx, NUVEC const* scale) {
    float sx = scale->x;
    mtx->m[0][0] *= sx;
    mtx->m[1][0] *= sx;
    mtx->m[2][0] *= sx;
    mtx->m[3][0] *= sx;
    float sy = scale->y;
    mtx->m[0][1] *= sy;
    mtx->m[1][1] *= sy;
    mtx->m[2][1] *= sy;
    mtx->m[3][1] *= sy;
    float sz = scale->z;
    mtx->m[0][2] *= sz;
    mtx->m[1][2] *= sz;
    mtx->m[2][2] *= sz;
    mtx->m[3][2] *= sz;
}
void NuMtxScaleU(NUMTX* mtx, float scale) {
    mtx->m[0][0] *= scale;
    mtx->m[0][1] *= scale;
    mtx->m[0][2] *= scale;
    mtx->m[1][0] *= scale;
    mtx->m[1][1] *= scale;
    mtx->m[1][2] *= scale;
    mtx->m[2][0] *= scale;
    mtx->m[2][1] *= scale;
    mtx->m[2][2] *= scale;
    mtx->m[3][0] *= scale;
    mtx->m[3][1] *= scale;
    mtx->m[3][2] *= scale;
}
void NuMtxPreTranslate(NUMTX* mtx, NUVEC const* translation) {
    float dx = translation->x * mtx->m[0][0] + translation->y * mtx->m[1][0] + translation->z * mtx->m[2][0];
    float dy = translation->x * mtx->m[0][1] + translation->y * mtx->m[1][1] + translation->z * mtx->m[2][1];
    float dz = translation->x * mtx->m[0][2] + translation->y * mtx->m[1][2] + translation->z * mtx->m[2][2];
    mtx->m[3][0] += dx;
    mtx->m[3][1] += dy;
    mtx->m[3][2] += dz;
}
void NuMtxPreTranslateX(NUMTX* mtx, float x) {
    mtx->m[3][0] += mtx->m[0][0] * x;
    mtx->m[3][1] += mtx->m[0][1] * x;
    mtx->m[3][2] += mtx->m[0][2] * x;
}
void NuMtxPreTranslateNeg(NUMTX* mtx, NUVEC const* translation) {
    float dx = translation->x * mtx->m[0][0] + translation->y * mtx->m[1][0] + translation->z * mtx->m[2][0];
    float dy = translation->x * mtx->m[0][1] + translation->y * mtx->m[1][1] + translation->z * mtx->m[2][1];
    float dz = translation->x * mtx->m[0][2] + translation->y * mtx->m[1][2] + translation->z * mtx->m[2][2];
    mtx->m[3][0] -= dx;
    mtx->m[3][1] -= dy;
    mtx->m[3][2] -= dz;
}
void NuMtxPreSkewYX(NUMTX* mtx, float skew) {
    mtx->m[0][0] += mtx->m[1][0] * skew;
    mtx->m[0][1] += mtx->m[1][1] * skew;
    mtx->m[0][2] += mtx->m[1][2] * skew;
}
void NuMtxPreRotateY180(NUMTX* mtx) {
    mtx->m[0][0] = -mtx->m[0][0];
    mtx->m[0][1] = -mtx->m[0][1];
    mtx->m[0][2] = -mtx->m[0][2];
    mtx->m[2][0] = -mtx->m[2][0];
    mtx->m[2][1] = -mtx->m[2][1];
    mtx->m[2][2] = -mtx->m[2][2];
}
void NuMtxPreRotateXRads(NUMTX* mtx, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float r10 = mtx->m[1][0], r11 = mtx->m[1][1], r12 = mtx->m[1][2];
    float r20 = mtx->m[2][0], r21 = mtx->m[2][1], r22 = mtx->m[2][2];
    mtx->m[1][0] = c * r10 + s * r20;
    mtx->m[1][1] = c * r11 + s * r21;
    mtx->m[1][2] = c * r12 + s * r22;
    mtx->m[2][0] = c * r20 - s * r10;
    mtx->m[2][1] = c * r21 - s * r11;
    mtx->m[2][2] = c * r22 - s * r12;
}
void NuMtxPreRotateYRads(NUMTX* mtx, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float r00 = mtx->m[0][0], r01 = mtx->m[0][1], r02 = mtx->m[0][2];
    float r20 = mtx->m[2][0], r21 = mtx->m[2][1], r22 = mtx->m[2][2];
    mtx->m[0][0] = c * r00 - s * r20;
    mtx->m[0][1] = c * r01 - s * r21;
    mtx->m[0][2] = c * r02 - s * r22;
    mtx->m[2][0] = s * r00 + c * r20;
    mtx->m[2][1] = s * r01 + c * r21;
    mtx->m[2][2] = s * r02 + c * r22;
}
void NuMtxPreRotateZRads(NUMTX* mtx, float rads) {
    float c = NuCosf(rads);
    float s = NuSinf(rads);
    float r00 = mtx->m[0][0], r01 = mtx->m[0][1], r02 = mtx->m[0][2];
    float r10 = mtx->m[1][0], r11 = mtx->m[1][1], r12 = mtx->m[1][2];
    mtx->m[0][0] = c * r00 + s * r10;
    mtx->m[0][1] = c * r01 + s * r11;
    mtx->m[0][2] = c * r02 + s * r12;
    mtx->m[1][0] = c * r10 - s * r00;
    mtx->m[1][1] = c * r11 - s * r01;
    mtx->m[1][2] = c * r12 - s * r02;
}
void NuMtxPreRotateXOld(NUMTX* mtx, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float r10 = mtx->m[1][0], r11 = mtx->m[1][1], r12 = mtx->m[1][2];
    float r20 = mtx->m[2][0], r21 = mtx->m[2][1], r22 = mtx->m[2][2];
    mtx->m[1][0] = c * r10 + s * r20;
    mtx->m[1][1] = c * r11 + s * r21;
    mtx->m[1][2] = c * r12 + s * r22;
    mtx->m[2][0] = c * r20 - s * r10;
    mtx->m[2][1] = c * r21 - s * r11;
    mtx->m[2][2] = c * r22 - s * r12;
}
void NuMtxPreRotateYOld(NUMTX* mtx, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float r00 = mtx->m[0][0], r01 = mtx->m[0][1], r02 = mtx->m[0][2];
    float r20 = mtx->m[2][0], r21 = mtx->m[2][1], r22 = mtx->m[2][2];
    mtx->m[0][0] = c * r00 - s * r20;
    mtx->m[0][1] = c * r01 - s * r21;
    mtx->m[0][2] = c * r02 - s * r22;
    mtx->m[2][0] = s * r00 + c * r20;
    mtx->m[2][1] = s * r01 + c * r21;
    mtx->m[2][2] = s * r02 + c * r22;
}
void NuMtxPreRotateZOld(NUMTX* mtx, int angle) {
    float c = NuSinOld(angle + 16384);
    float s = NuSinOld(angle);
    float r00 = mtx->m[0][0], r01 = mtx->m[0][1], r02 = mtx->m[0][2];
    float r10 = mtx->m[1][0], r11 = mtx->m[1][1], r12 = mtx->m[1][2];
    mtx->m[0][0] = c * r00 + s * r10;
    mtx->m[0][1] = c * r01 + s * r11;
    mtx->m[0][2] = c * r02 + s * r12;
    mtx->m[1][0] = c * r10 - s * r00;
    mtx->m[1][1] = c * r11 - s * r01;
    mtx->m[1][2] = c * r12 - s * r02;
}
void NuMtxPreScale(NUMTX* mtx, NUVEC const* scale) {
    float sx = scale->x;
    mtx->m[0][0] = sx * mtx->m[0][0];
    mtx->m[0][1] = sx * mtx->m[0][1];
    mtx->m[0][2] = sx * mtx->m[0][2];
    float sy = scale->y;
    mtx->m[1][0] = sy * mtx->m[1][0];
    mtx->m[1][1] = sy * mtx->m[1][1];
    mtx->m[1][2] = sy * mtx->m[1][2];
    float sz = scale->z;
    mtx->m[2][0] = sz * mtx->m[2][0];
    mtx->m[2][1] = sz * mtx->m[2][1];
    mtx->m[2][2] = sz * mtx->m[2][2];
}
void NuMtxPreScaleVU0(NUMTX* mtx, NUVEC const* scale) {
    float sx = scale->x;
    mtx->m[0][0] = sx * mtx->m[0][0];
    mtx->m[0][1] = sx * mtx->m[0][1];
    mtx->m[0][2] = sx * mtx->m[0][2];
    float sy = scale->y;
    mtx->m[1][0] = sy * mtx->m[1][0];
    mtx->m[1][1] = sy * mtx->m[1][1];
    mtx->m[1][2] = sy * mtx->m[1][2];
    float sz = scale->z;
    mtx->m[2][0] = sz * mtx->m[2][0];
    mtx->m[2][1] = sz * mtx->m[2][1];
    mtx->m[2][2] = sz * mtx->m[2][2];
}
void NuMtxPreScaleU(NUMTX* mtx, float scale) {
    mtx->m[0][0] *= scale;
    mtx->m[0][1] *= scale;
    mtx->m[0][2] *= scale;
    mtx->m[1][0] *= scale;
    mtx->m[1][1] *= scale;
    mtx->m[1][2] *= scale;
    mtx->m[2][0] *= scale;
    mtx->m[2][1] *= scale;
    mtx->m[2][2] *= scale;
}
void NuMtxPreScaleX(NUMTX* mtx, float x) {
    mtx->m[0][0] *= x;
    mtx->m[0][1] *= x;
    mtx->m[0][2] *= x;
}
void NuMtxSkewSymmetric(NUMTX* mtx, NUVEC const* v) {
    mtx->m[0][0] = 0.0f;
    mtx->m[0][1] = -v->z;
    mtx->m[0][2] = v->y;
    mtx->m[0][3] = 0.0f;
    mtx->m[1][0] = -mtx->m[0][1];
    mtx->m[1][1] = 0.0f;
    mtx->m[1][2] = -v->x;
    mtx->m[1][3] = 0.0f;
    mtx->m[2][0] = -mtx->m[0][2];
    mtx->m[2][1] = -mtx->m[1][2];
    mtx->m[2][2] = 0.0f;
    mtx->m[2][3] = 0.0f;
    mtx->m[3][0] = 0.0f;
    mtx->m[3][1] = 0.0f;
    mtx->m[3][2] = 0.0f;
    mtx->m[3][3] = 1.0f;
}
float NuMtxDet3(NUMTX const* mtx) {
    return mtx->m[0][0] * (mtx->m[1][1] * mtx->m[2][2] - mtx->m[1][2] * mtx->m[2][1])
           - mtx->m[0][1] * (mtx->m[1][0] * mtx->m[2][2] - mtx->m[1][2] * mtx->m[2][0])
           + mtx->m[0][2] * (mtx->m[1][0] * mtx->m[2][1] - mtx->m[1][1] * mtx->m[2][0]);
}
void NuMtxInvR(NUMTX* out, NUMTX const* src) {
    float t;
    t = src->m[0][1];
    out->m[0][1] = src->m[1][0];
    out->m[1][0] = t;
    t = src->m[0][2];
    out->m[0][2] = src->m[2][0];
    out->m[2][0] = t;
    t = src->m[1][2];
    out->m[1][2] = src->m[2][1];
    out->m[2][1] = t;
    out->m[0][0] = src->m[0][0];
    out->m[1][1] = src->m[1][1];
    out->m[2][2] = src->m[2][2];
    out->m[1][3] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxGetEulerXYZOld(NUMTX const* mtx, int* outX, int* outY, int* outZ) {
    NUVEC xAxis;
    NUVEC zAxis;
    NuMtxGetXAxis(mtx, &xAxis);
    NuMtxGetZAxis(mtx, &zAxis);
    NuMtxVecToEulerXYZOld(&xAxis, &zAxis, outX, outY, outZ);
}
void NuMtxGetEulerXYZRads(NUMTX const* mtx, float* outX, float* outY, float* outZ) {
    NUVEC xAxis;
    NUVEC zAxis;
    NuMtxGetXAxis(mtx, &xAxis);
    NuMtxGetZAxis(mtx, &zAxis);
    NuMtxVecToEulerXYZRads(&xAxis, &zAxis, outX, outY, outZ);
}
void NuMtxAlignX(NUMTX* out, NUVEC const* vec) {
    out->m[0][0] = vec->x;
    out->m[0][1] = vec->y;
    out->m[0][2] = vec->z;

    float zx = out->m[0][1] * out->m[1][2] - out->m[0][2] * out->m[1][1];
    float zy = out->m[0][2] * out->m[1][0] - out->m[0][0] * out->m[1][2];
    float zz = out->m[0][0] * out->m[1][1] - out->m[0][1] * out->m[1][0];
    out->m[2][0] = zx;
    out->m[2][1] = zy;
    out->m[2][2] = zz;

    float mag = NuFsqrt(zx * zx + zy * zy + zz * zz);
    float invMag;
    if (mag != 0.0f) {
        invMag = 1.0f / mag;
    } else {
        invMag = 0.0f;
    }
    zx = out->m[2][0] * invMag;
    zy = invMag * out->m[2][1];
    zz = invMag * out->m[2][2];
    out->m[2][0] = zx;
    out->m[2][1] = zy;
    out->m[2][2] = zz;

    out->m[1][0] = zy * out->m[0][2] - zz * out->m[0][1];
    out->m[1][1] = zz * out->m[0][0] - zx * out->m[0][2];
    out->m[1][2] = zx * out->m[0][1] - zy * out->m[0][0];
}
void NuMtxAlignY(NUMTX* out, NUVEC const* vec) {
    out->m[1][0] = vec->x;
    out->m[1][1] = vec->y;
    out->m[1][2] = vec->z;

    float zx = out->m[1][1] * out->m[2][2] - out->m[1][2] * out->m[2][1];
    float zy = out->m[1][2] * out->m[2][0] - out->m[1][0] * out->m[2][2];
    float zz = out->m[1][0] * out->m[2][1] - out->m[1][1] * out->m[2][0];
    out->m[0][0] = zx;
    out->m[0][1] = zy;
    out->m[0][2] = zz;

    float mag = NuFsqrt(zx * zx + zy * zy + zz * zz);
    float invMag;
    if (mag != 0.0f) {
        invMag = 1.0f / mag;
    } else {
        invMag = 0.0f;
    }
    zx = out->m[0][0] * invMag;
    zy = invMag * out->m[0][1];
    zz = invMag * out->m[0][2];
    out->m[0][0] = zx;
    out->m[0][1] = zy;
    out->m[0][2] = zz;

    out->m[2][0] = zy * out->m[1][2] - zz * out->m[1][1];
    out->m[2][1] = zz * out->m[1][0] - zx * out->m[1][2];
    out->m[2][2] = zx * out->m[1][1] - zy * out->m[1][0];
}
#define NU_MTX_ALIGNZ_RESCALE_ROW(row, origSq)                                                               \
    do {                                                                                                     \
        float newSq = (row)[0] * (row)[0] + (row)[1] * (row)[1] + (row)[2] * (row)[2];                       \
        float prod = (origSq) * newSq;                                                                       \
        float ratio = prod == 0.0f ? 0.0f : (origSq) / newSq;                                                \
        float scale = 0.0f;                                                                                  \
        if (!(ratio <= 0.0f)) {                                                                              \
            scale = sqrtf(ratio);                                                                            \
        }                                                                                                    \
        (row)[0] = scale * (row)[0];                                                                         \
        (row)[1] = scale * (row)[1];                                                                         \
        (row)[2] = scale * (row)[2];                                                                         \
    } while (0)
void NuMtxAlignZ(NUMTX* out, NUVEC const* vec) {
    float m0sq = out->m[0][0] * out->m[0][0] + out->m[0][1] * out->m[0][1] + out->m[0][2] * out->m[0][2];
    float m1sq = out->m[1][0] * out->m[1][0] + out->m[1][1] * out->m[1][1] + out->m[1][2] * out->m[1][2];
    float m2sq = out->m[2][0] * out->m[2][0] + out->m[2][1] * out->m[2][1] + out->m[2][2] * out->m[2][2];
    float vsq = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;

    float ratio = m2sq * vsq == 0.0f ? 0.0f : m2sq / vsq;
    float scale = 0.0f;
    if (!(ratio <= 0.0f)) {
        scale = sqrtf(ratio);
    }
    float sx = scale * vec->x;
    float sy = scale * vec->y;
    float sz = scale * vec->z;
    out->m[2][0] = sx;
    out->m[2][1] = sy;
    out->m[2][2] = sz;

    NUVEC* r0 = reinterpret_cast<NUVEC*>(out->m[0]);
    NUVEC* r1 = reinterpret_cast<NUVEC*>(out->m[1]);
    NUVEC* r2 = reinterpret_cast<NUVEC*>(out->m[2]);
    float d = NuVecDot(r1, r2);
    float ad = d >= 0.0f ? d : -d;
    if (ad > 0.8660254f) {
        NuVecCross(r1, r2, r0);
        NU_MTX_ALIGNZ_RESCALE_ROW(out->m[1], m1sq);
        NuVecCross(r0, r1, r2);
        NU_MTX_ALIGNZ_RESCALE_ROW(out->m[0], m0sq);
    } else {
        NuVecCross(r0, r1, r2);
        NU_MTX_ALIGNZ_RESCALE_ROW(out->m[0], m0sq);
        NuVecCross(r0, r1, r2);
        NU_MTX_ALIGNZ_RESCALE_ROW(out->m[1], m1sq);
    }
}
#undef NU_MTX_ALIGNZ_RESCALE_ROW
void NuMtxLookAtX(NUMTX* out, NUVEC const* target) {
    NUVEC dir;
    dir.x = target->x - out->m[3][0];
    dir.y = target->y - out->m[3][1];
    dir.z = target->z - out->m[3][2];
    NuVecNorm(&dir, &dir);
    NuMtxAlignX(out, &dir);
}
void NuMtxLookAtY(NUMTX* out, NUVEC const* target) {
    NUVEC dir;
    dir.x = target->x - out->m[3][0];
    dir.y = target->y - out->m[3][1];
    dir.z = target->z - out->m[3][2];
    NuVecNorm(&dir, &dir);
    NuMtxAlignY(out, &dir);
}
void NuMtxLookAtZ(NUMTX* out, NUVEC const* target) {
    NUVEC dir;
    dir.x = target->x - out->m[3][0];
    dir.y = target->y - out->m[3][1];
    dir.z = target->z - out->m[3][2];
    NuVecNorm(&dir, &dir);
    NuMtxAlignZ(out, &dir);
}
void NuMtxInvLookAtZ(NUMTX* out, NUVEC const* target) {
    NUVEC dir;
    dir.x = out->m[3][0] - target->x;
    dir.y = out->m[3][1] - target->y;
    dir.z = out->m[3][2] - target->z;
    NuVecNorm(&dir, &dir);
    NuMtxAlignZ(out, &dir);
}
void NuMtxInvLookAtX(NUMTX* out, NUVEC const* target) {
    NUVEC dir;
    dir.x = out->m[3][0] - target->x;
    dir.y = out->m[3][1] - target->y;
    dir.z = out->m[3][2] - target->z;
    NuVecNorm(&dir, &dir);
    NuMtxAlignX(out, &dir);
}
void NuMtxInvLookAtY(NUMTX* out, NUVEC const* target) {
    NUVEC dir;
    dir.x = out->m[3][0] - target->x;
    dir.y = out->m[3][1] - target->y;
    dir.z = out->m[3][2] - target->z;
    NuVecNorm(&dir, &dir);
    NuMtxAlignY(out, &dir);
}
void NuMtxLookAtD3D(NUMTX* out, NUVEC const* eye, NUVEC const* at, NUVEC const* up) {
    NUVEC side, up2, fwd;
    NuVecSub(&fwd, at, eye);
    NuVecNorm(&fwd, &fwd);
    NuVecCross(&side, up, &fwd);
    NuVecNorm(&side, &side);
    NuVecCross(&up2, &fwd, &side);
    NuVecNorm(&up2, &up2);
    out->m[0][0] = side.x;
    out->m[0][1] = up2.x;
    out->m[0][2] = fwd.x;
    out->m[0][3] = 0.0f;
    out->m[1][0] = side.y;
    out->m[1][1] = up2.y;
    out->m[1][2] = fwd.y;
    out->m[1][3] = 0.0f;
    out->m[2][0] = side.z;
    out->m[2][1] = up2.z;
    out->m[2][2] = fwd.z;
    out->m[2][3] = 0.0f;
    float tx = -(eye->x * side.x) - eye->y * side.y - eye->z * side.z;
    float ty = -(eye->x * up2.x) - eye->y * up2.y - eye->z * up2.z;
    float tz = -(eye->x * fwd.x) - eye->y * fwd.y - eye->z * fwd.z;
    out->m[3][0] = tx;
    out->m[3][1] = ty;
    out->m[3][2] = tz;
    out->m[3][3] = 1.0f;
}
void NuMtxLookAtInverseD3D(NUMTX* out, NUVEC const* eye, NUVEC const* at, NUVEC const* up) {
    NUVEC side, up2, fwd;
    NuVecSub(&fwd, at, eye);
    NuVecNorm(&fwd, &fwd);
    NuVecCross(&side, up, &fwd);
    NuVecNorm(&side, &side);
    NuVecCross(&up2, &fwd, &side);
    NuVecNorm(&up2, &up2);
    out->m[0][0] = side.x;
    out->m[0][1] = side.y;
    out->m[0][2] = side.z;
    out->m[0][3] = 0.0f;
    out->m[1][0] = up2.x;
    out->m[1][1] = up2.y;
    out->m[1][2] = up2.z;
    out->m[1][3] = 0.0f;
    out->m[2][0] = fwd.x;
    out->m[2][1] = fwd.y;
    out->m[2][2] = fwd.z;
    out->m[2][3] = 0.0f;
    out->m[3][0] = eye->x;
    out->m[3][1] = eye->y;
    out->m[3][2] = eye->z;
    out->m[3][3] = 1.0f;
}
void NuMtxMul(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs) {
    float l00 = lhs->m[0][0], l01 = lhs->m[0][1], l02 = lhs->m[0][2];
    float m00 = (l00 * rhs->m[0][0] + l01 * rhs->m[1][0]) + l02 * rhs->m[2][0];
    if (out == lhs || out == rhs) {
        float m01 = (l00 * rhs->m[0][1] + l01 * rhs->m[1][1]) + l02 * rhs->m[2][1];
        float m02 = (l00 * rhs->m[0][2] + l01 * rhs->m[1][2]) + l02 * rhs->m[2][2];
        float l10 = lhs->m[1][0], l11 = lhs->m[1][1], l12 = lhs->m[1][2];
        float m10 = (l10 * rhs->m[0][0] + l11 * rhs->m[1][0]) + l12 * rhs->m[2][0];
        float m11 = (l10 * rhs->m[0][1] + l11 * rhs->m[1][1]) + l12 * rhs->m[2][1];
        float m12 = (l10 * rhs->m[0][2] + l11 * rhs->m[1][2]) + l12 * rhs->m[2][2];
        float l20 = lhs->m[2][0], l21 = lhs->m[2][1], l22 = lhs->m[2][2];
        float m20 = (l20 * rhs->m[0][0] + l21 * rhs->m[1][0]) + l22 * rhs->m[2][0];
        float m21 = (l20 * rhs->m[0][1] + l21 * rhs->m[1][1]) + l22 * rhs->m[2][1];
        float m22 = (l20 * rhs->m[0][2] + l21 * rhs->m[1][2]) + l22 * rhs->m[2][2];
        float l30 = lhs->m[3][0], l31 = lhs->m[3][1], l32 = lhs->m[3][2];
        float m30 = rhs->m[3][0] + ((l30 * rhs->m[0][0] + l31 * rhs->m[1][0]) + l32 * rhs->m[2][0]);
        float m31 = rhs->m[3][1] + ((l30 * rhs->m[0][1] + l31 * rhs->m[1][1]) + l32 * rhs->m[2][1]);
        float m32 = rhs->m[3][2] + ((l30 * rhs->m[0][2] + l31 * rhs->m[1][2]) + l32 * rhs->m[2][2]);
        out->m[0][0] = m00;
        out->m[0][1] = m01;
        out->m[0][2] = m02;
        out->m[0][3] = 0.0f;
        out->m[1][0] = m10;
        out->m[1][1] = m11;
        out->m[1][2] = m12;
        out->m[1][3] = 0.0f;
        out->m[2][0] = m20;
        out->m[2][1] = m21;
        out->m[2][2] = m22;
        out->m[2][3] = 0.0f;
        out->m[3][0] = m30;
        out->m[3][1] = m31;
        out->m[3][2] = m32;
    } else {
        out->m[0][0] = m00;
        out->m[0][1] = (l00 * rhs->m[0][1] + l01 * rhs->m[1][1]) + l02 * rhs->m[2][1];
        out->m[0][2] = (l00 * rhs->m[0][2] + l01 * rhs->m[1][2]) + l02 * rhs->m[2][2];
        out->m[0][3] = 0.0f;
        float l10 = lhs->m[1][0], l11 = lhs->m[1][1], l12 = lhs->m[1][2];
        out->m[1][0] = (l10 * rhs->m[0][0] + l11 * rhs->m[1][0]) + l12 * rhs->m[2][0];
        out->m[1][1] = (l10 * rhs->m[0][1] + l11 * rhs->m[1][1]) + l12 * rhs->m[2][1];
        out->m[1][2] = (l10 * rhs->m[0][2] + l11 * rhs->m[1][2]) + l12 * rhs->m[2][2];
        out->m[1][3] = 0.0f;
        float l20 = lhs->m[2][0], l21 = lhs->m[2][1], l22 = lhs->m[2][2];
        out->m[2][0] = (l20 * rhs->m[0][0] + l21 * rhs->m[1][0]) + l22 * rhs->m[2][0];
        out->m[2][1] = (l20 * rhs->m[0][1] + l21 * rhs->m[1][1]) + l22 * rhs->m[2][1];
        out->m[2][2] = (l20 * rhs->m[0][2] + l21 * rhs->m[1][2]) + l22 * rhs->m[2][2];
        out->m[2][3] = 0.0f;
        float l30 = lhs->m[3][0], l31 = lhs->m[3][1], l32 = lhs->m[3][2];
        out->m[3][0] = rhs->m[3][0] + ((l30 * rhs->m[0][0] + l31 * rhs->m[1][0]) + l32 * rhs->m[2][0]);
        out->m[3][1] = rhs->m[3][1] + ((l30 * rhs->m[0][1] + l31 * rhs->m[1][1]) + l32 * rhs->m[2][1]);
        out->m[3][2] = rhs->m[3][2] + ((l30 * rhs->m[0][2] + l31 * rhs->m[1][2]) + l32 * rhs->m[2][2]);
    }
    out->m[3][3] = 1.0f;
}
void NuMtxMulR(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs) {
    float l00 = lhs->m[0][0], l01 = lhs->m[0][1], l02 = lhs->m[0][2];
    float m00 = (l00 * rhs->m[0][0] + l01 * rhs->m[1][0]) + l02 * rhs->m[2][0];
    if (out == lhs || out == rhs) {
        float m01 = (l00 * rhs->m[0][1] + l01 * rhs->m[1][1]) + l02 * rhs->m[2][1];
        float m02 = (l00 * rhs->m[0][2] + l01 * rhs->m[1][2]) + l02 * rhs->m[2][2];
        float l10 = lhs->m[1][0], l11 = lhs->m[1][1], l12 = lhs->m[1][2];
        float m10 = (l10 * rhs->m[0][0] + l11 * rhs->m[1][0]) + l12 * rhs->m[2][0];
        float m11 = (l10 * rhs->m[0][1] + l11 * rhs->m[1][1]) + l12 * rhs->m[2][1];
        float m12 = (l10 * rhs->m[0][2] + l11 * rhs->m[1][2]) + l12 * rhs->m[2][2];
        float l20 = lhs->m[2][0], l21 = lhs->m[2][1], l22 = lhs->m[2][2];
        float m20 = (l20 * rhs->m[0][0] + l21 * rhs->m[1][0]) + l22 * rhs->m[2][0];
        float m21 = (l20 * rhs->m[0][1] + l21 * rhs->m[1][1]) + l22 * rhs->m[2][1];
        float m22 = (l20 * rhs->m[0][2] + l21 * rhs->m[1][2]) + l22 * rhs->m[2][2];
        out->m[0][0] = m00;
        out->m[0][1] = m01;
        out->m[0][2] = m02;
        out->m[0][3] = 0.0f;
        out->m[1][0] = m10;
        out->m[1][1] = m11;
        out->m[1][2] = m12;
        out->m[1][3] = 0.0f;
        out->m[2][0] = m20;
        out->m[2][1] = m21;
        out->m[2][2] = m22;
        out->m[2][3] = 0.0f;
    } else {
        out->m[0][0] = m00;
        out->m[0][1] = (l00 * rhs->m[0][1] + l01 * rhs->m[1][1]) + l02 * rhs->m[2][1];
        out->m[0][2] = (l00 * rhs->m[0][2] + l01 * rhs->m[1][2]) + l02 * rhs->m[2][2];
        out->m[0][3] = 0.0f;
        float l10 = lhs->m[1][0], l11 = lhs->m[1][1], l12 = lhs->m[1][2];
        out->m[1][0] = (l10 * rhs->m[0][0] + l11 * rhs->m[1][0]) + l12 * rhs->m[2][0];
        out->m[1][1] = (l10 * rhs->m[0][1] + l11 * rhs->m[1][1]) + l12 * rhs->m[2][1];
        out->m[1][2] = (l10 * rhs->m[0][2] + l11 * rhs->m[1][2]) + l12 * rhs->m[2][2];
        out->m[1][3] = 0.0f;
        float l20 = lhs->m[2][0], l21 = lhs->m[2][1], l22 = lhs->m[2][2];
        out->m[2][0] = (l20 * rhs->m[0][0] + l21 * rhs->m[1][0]) + l22 * rhs->m[2][0];
        out->m[2][1] = (l20 * rhs->m[0][1] + l21 * rhs->m[1][1]) + l22 * rhs->m[2][1];
        out->m[2][2] = (l20 * rhs->m[0][2] + l21 * rhs->m[1][2]) + l22 * rhs->m[2][2];
        out->m[2][3] = 0.0f;
    }
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxMulH(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs) {
    float l00 = lhs->m[0][0], l01 = lhs->m[0][1], l02 = lhs->m[0][2], l03 = lhs->m[0][3];
    float m00 = (((l00 * rhs->m[0][0] + l01 * rhs->m[1][0]) + l02 * rhs->m[2][0]) + l03 * rhs->m[3][0]);
    if (out == lhs || out == rhs) {
        float m01 = (((l00 * rhs->m[0][1] + l01 * rhs->m[1][1]) + l02 * rhs->m[2][1]) + l03 * rhs->m[3][1]);
        float m02 = (((l00 * rhs->m[0][2] + l01 * rhs->m[1][2]) + l02 * rhs->m[2][2]) + l03 * rhs->m[3][2]);
        float m03 = (((l00 * rhs->m[0][3] + l01 * rhs->m[1][3]) + l02 * rhs->m[2][3]) + l03 * rhs->m[3][3]);
        float l10 = lhs->m[1][0], l11 = lhs->m[1][1], l12 = lhs->m[1][2], l13 = lhs->m[1][3];
        float m10 = (((l10 * rhs->m[0][0] + l11 * rhs->m[1][0]) + l12 * rhs->m[2][0]) + l13 * rhs->m[3][0]);
        float m11 = (((l10 * rhs->m[0][1] + l11 * rhs->m[1][1]) + l12 * rhs->m[2][1]) + l13 * rhs->m[3][1]);
        float m12 = (((l10 * rhs->m[0][2] + l11 * rhs->m[1][2]) + l12 * rhs->m[2][2]) + l13 * rhs->m[3][2]);
        float m13 = (((l10 * rhs->m[0][3] + l11 * rhs->m[1][3]) + l12 * rhs->m[2][3]) + l13 * rhs->m[3][3]);
        float l20 = lhs->m[2][0], l21 = lhs->m[2][1], l22 = lhs->m[2][2], l23 = lhs->m[2][3];
        float m20 = (((l20 * rhs->m[0][0] + l21 * rhs->m[1][0]) + l22 * rhs->m[2][0]) + l23 * rhs->m[3][0]);
        float m21 = (((l20 * rhs->m[0][1] + l21 * rhs->m[1][1]) + l22 * rhs->m[2][1]) + l23 * rhs->m[3][1]);
        float m22 = (((l20 * rhs->m[0][2] + l21 * rhs->m[1][2]) + l22 * rhs->m[2][2]) + l23 * rhs->m[3][2]);
        float m23 = (((l20 * rhs->m[0][3] + l21 * rhs->m[1][3]) + l22 * rhs->m[2][3]) + l23 * rhs->m[3][3]);
        float l30 = lhs->m[3][0], l31 = lhs->m[3][1], l32 = lhs->m[3][2], l33 = lhs->m[3][3];
        float m30 = (((l30 * rhs->m[0][0] + l31 * rhs->m[1][0]) + l32 * rhs->m[2][0]) + l33 * rhs->m[3][0]);
        float m31 = (((l30 * rhs->m[0][1] + l31 * rhs->m[1][1]) + l32 * rhs->m[2][1]) + l33 * rhs->m[3][1]);
        float m32 = (((l30 * rhs->m[0][2] + l31 * rhs->m[1][2]) + l32 * rhs->m[2][2]) + l33 * rhs->m[3][2]);
        float m33 = (((l30 * rhs->m[0][3] + l31 * rhs->m[1][3]) + l32 * rhs->m[2][3]) + l33 * rhs->m[3][3]);
        out->m[0][0] = m00;
        out->m[0][1] = m01;
        out->m[0][2] = m02;
        out->m[0][3] = m03;
        out->m[1][0] = m10;
        out->m[1][1] = m11;
        out->m[1][2] = m12;
        out->m[1][3] = m13;
        out->m[2][0] = m20;
        out->m[2][1] = m21;
        out->m[2][2] = m22;
        out->m[2][3] = m23;
        out->m[3][0] = m30;
        out->m[3][1] = m31;
        out->m[3][2] = m32;
        out->m[3][3] = m33;
    } else {
        out->m[0][0] = m00;
        out->m[0][1]
            = (((l00 * rhs->m[0][1] + l01 * rhs->m[1][1]) + l02 * rhs->m[2][1]) + l03 * rhs->m[3][1]);
        out->m[0][2]
            = (((l00 * rhs->m[0][2] + l01 * rhs->m[1][2]) + l02 * rhs->m[2][2]) + l03 * rhs->m[3][2]);
        out->m[0][3]
            = (((l00 * rhs->m[0][3] + l01 * rhs->m[1][3]) + l02 * rhs->m[2][3]) + l03 * rhs->m[3][3]);
        float l10 = lhs->m[1][0], l11 = lhs->m[1][1], l12 = lhs->m[1][2], l13 = lhs->m[1][3];
        out->m[1][0]
            = (((l10 * rhs->m[0][0] + l11 * rhs->m[1][0]) + l12 * rhs->m[2][0]) + l13 * rhs->m[3][0]);
        out->m[1][1]
            = (((l10 * rhs->m[0][1] + l11 * rhs->m[1][1]) + l12 * rhs->m[2][1]) + l13 * rhs->m[3][1]);
        out->m[1][2]
            = (((l10 * rhs->m[0][2] + l11 * rhs->m[1][2]) + l12 * rhs->m[2][2]) + l13 * rhs->m[3][2]);
        out->m[1][3]
            = (((l10 * rhs->m[0][3] + l11 * rhs->m[1][3]) + l12 * rhs->m[2][3]) + l13 * rhs->m[3][3]);
        float l20 = lhs->m[2][0], l21 = lhs->m[2][1], l22 = lhs->m[2][2], l23 = lhs->m[2][3];
        out->m[2][0]
            = (((l20 * rhs->m[0][0] + l21 * rhs->m[1][0]) + l22 * rhs->m[2][0]) + l23 * rhs->m[3][0]);
        out->m[2][1]
            = (((l20 * rhs->m[0][1] + l21 * rhs->m[1][1]) + l22 * rhs->m[2][1]) + l23 * rhs->m[3][1]);
        out->m[2][2]
            = (((l20 * rhs->m[0][2] + l21 * rhs->m[1][2]) + l22 * rhs->m[2][2]) + l23 * rhs->m[3][2]);
        out->m[2][3]
            = (((l20 * rhs->m[0][3] + l21 * rhs->m[1][3]) + l22 * rhs->m[2][3]) + l23 * rhs->m[3][3]);
        float l30 = lhs->m[3][0], l31 = lhs->m[3][1], l32 = lhs->m[3][2], l33 = lhs->m[3][3];
        out->m[3][0]
            = (((l30 * rhs->m[0][0] + l31 * rhs->m[1][0]) + l32 * rhs->m[2][0]) + l33 * rhs->m[3][0]);
        out->m[3][1]
            = (((l30 * rhs->m[0][1] + l31 * rhs->m[1][1]) + l32 * rhs->m[2][1]) + l33 * rhs->m[3][1]);
        out->m[3][2]
            = (((l30 * rhs->m[0][2] + l31 * rhs->m[1][2]) + l32 * rhs->m[2][2]) + l33 * rhs->m[3][2]);
        out->m[3][3]
            = (((l30 * rhs->m[0][3] + l31 * rhs->m[1][3]) + l32 * rhs->m[2][3]) + l33 * rhs->m[3][3]);
    }
}
void NuMtxAddR(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs) {
    out->m[0][0] = lhs->m[0][0] + rhs->m[0][0];
    out->m[0][1] = lhs->m[0][1] + rhs->m[0][1];
    out->m[0][2] = lhs->m[0][2] + rhs->m[0][2];
    out->m[0][3] = 0.0f;
    out->m[1][0] = lhs->m[1][0] + rhs->m[1][0];
    out->m[1][1] = lhs->m[1][1] + rhs->m[1][1];
    out->m[1][2] = lhs->m[1][2] + rhs->m[1][2];
    out->m[1][3] = 0.0f;
    out->m[2][0] = lhs->m[2][0] + rhs->m[2][0];
    out->m[2][1] = lhs->m[2][1] + rhs->m[2][1];
    out->m[2][2] = lhs->m[2][2] + rhs->m[2][2];
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxSubR(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs) {
    out->m[0][0] = lhs->m[0][0] - rhs->m[0][0];
    out->m[0][1] = lhs->m[0][1] - rhs->m[0][1];
    out->m[0][2] = lhs->m[0][2] - rhs->m[0][2];
    out->m[0][3] = 0.0f;
    out->m[1][0] = lhs->m[1][0] - rhs->m[1][0];
    out->m[1][1] = lhs->m[1][1] - rhs->m[1][1];
    out->m[1][2] = lhs->m[1][2] - rhs->m[1][2];
    out->m[1][3] = 0.0f;
    out->m[2][0] = lhs->m[2][0] - rhs->m[2][0];
    out->m[2][1] = lhs->m[2][1] - rhs->m[2][1];
    out->m[2][2] = lhs->m[2][2] - rhs->m[2][2];
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
int NuMtxCompare(NUMTX const* m1, NUMTX const* m2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m1->m[i][j] > m2->m[i][j]) {
                return 1;
            }
            if (m1->m[i][j] < m2->m[i][j]) {
                return -1;
            }
        }
    }
    return 0;
}
float NuMtxSSE(NUMTX const* m1, NUMTX const* m2) {
    const float* p1 = &m1->m[0][0];
    const float* p2 = &m2->m[0][0];
    float d = p1[0] - p2[0];
    float sum = d * d;
    for (int i = 1; i < 16; i++) {
        d = p1[i] - p2[i];
        sum += d * d;
    }
    return sum;
}
void NuMtxTruncate24Bit(NUMTX* out, NUMTX const* src) {
    const unsigned int* in = (const unsigned int*)src;
    unsigned int* dst = (unsigned int*)out;
    for (int i = 0; i < 16; i++) {
        dst[i] = in[i] & 0xffffff00;
    }
}
void NuMtxInv(NUMTX* out, NUMTX const* in) {
    float tx = in->m[3][0];
    float ty = in->m[3][1];
    float tz = in->m[3][2];
    float t;
    t = in->m[0][1];
    out->m[0][1] = in->m[1][0];
    out->m[1][0] = t;
    t = in->m[0][2];
    out->m[0][2] = in->m[2][0];
    out->m[2][0] = t;
    t = in->m[1][2];
    out->m[1][2] = in->m[2][1];
    out->m[2][1] = t;
    out->m[0][0] = in->m[0][0];
    out->m[1][1] = in->m[1][1];
    out->m[2][2] = in->m[2][2];
    float negX = -tx;
    float negY = -ty;
    float negZ = -tz;
    out->m[3][0] = out->m[0][0] * negX + out->m[1][0] * negY + out->m[2][0] * negZ;
    out->m[3][1] = out->m[0][1] * negX + out->m[1][1] * negY + out->m[2][1] * negZ;
    out->m[3][2] = out->m[0][2] * negX + out->m[1][2] * negY + out->m[2][2] * negZ;
    out->m[2][3] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[0][3] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxInvVU0(NUMTX* out, NUMTX const* src) {
    float m30 = src->m[3][0];
    float m31 = src->m[3][1];
    float m32 = src->m[3][2];
    float t;
    t = src->m[0][1];
    out->m[0][1] = src->m[1][0];
    out->m[1][0] = t;
    t = src->m[0][2];
    out->m[0][2] = src->m[2][0];
    out->m[2][0] = t;
    t = src->m[1][2];
    out->m[1][2] = src->m[2][1];
    out->m[2][1] = t;
    out->m[0][0] = src->m[0][0];
    out->m[1][1] = src->m[1][1];
    out->m[2][2] = src->m[2][2];
    out->m[0][3] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][3] = 0.0f;
    float ntx = -m30;
    out->m[3][0] = out->m[0][0] * ntx - out->m[1][0] * m31 - out->m[2][0] * m32;
    out->m[3][1] = out->m[0][1] * ntx - out->m[1][1] * m31 - out->m[2][1] * m32;
    out->m[3][2] = out->m[0][2] * ntx - out->m[1][2] * m31 - out->m[2][2] * m32;
    out->m[3][3] = 1.0f;
}
void NuMtxInvTranspose3x3(NUMTX* out, NUMTX const* src) {
    float a = src->m[0][0];
    float b = src->m[0][1];
    float c = src->m[0][2];
    float d = src->m[1][0];
    float e = src->m[1][1];
    float f = src->m[1][2];
    float g = src->m[2][0];
    float h = src->m[2][1];
    float i = src->m[2][2];
    float A = e * i - f * h;
    float t0 = i * d - f * g;
    float t1 = h * d - e * g;
    float det = a * A - b * t0 + c * t1;
    float invDet = (det != 0.0f) ? 1.0f / det : 0.0f;
    float negInvDet = -invDet;
    out->m[0][0] = A * invDet;
    out->m[0][1] = t0 * negInvDet;
    out->m[0][2] = t1 * invDet;
    out->m[1][0] = (i * b - h * c) * negInvDet;
    out->m[1][1] = (a * i - g * c) * invDet;
    out->m[1][2] = (a * h - b * g) * negInvDet;
    out->m[2][0] = (f * b - e * c) * invDet;
    out->m[2][1] = (a * f - d * c) * negInvDet;
    out->m[2][2] = (a * e - b * d) * invDet;
    out->m[0][3] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxInvRSS(NUMTX* out, NUMTX const* src) {
    float a = src->m[0][0];
    float b = src->m[0][1];
    float c = src->m[0][2];
    float d = src->m[1][0];
    float e = src->m[1][1];
    float f = src->m[1][2];
    float g = src->m[2][0];
    float h = src->m[2][1];
    float i = src->m[2][2];
    float A = e * i - f * h;
    float t0 = i * d - f * g;
    float t1 = h * d - e * g;
    float det = a * A - b * t0 + c * t1;
    float invDet = (det != 0.0f) ? 1.0f / det : 0.0f;
    float negInvDet = -invDet;
    out->m[0][0] = A * invDet;
    out->m[1][0] = t0 * negInvDet;
    out->m[2][0] = t1 * invDet;
    out->m[0][1] = (i * b - h * c) * negInvDet;
    out->m[1][1] = (a * i - g * c) * invDet;
    out->m[2][1] = (a * h - b * g) * negInvDet;
    out->m[0][2] = (f * b - e * c) * invDet;
    out->m[1][2] = (a * f - d * c) * negInvDet;
    out->m[2][2] = (a * e - b * d) * invDet;
    out->m[0][3] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
void NuMtxInvRSSH(NUMTX* out, NUMTX const* src) {
    float a = src->m[0][0];
    float b = src->m[0][1];
    float c = src->m[0][2];
    float d = src->m[1][0];
    float e = src->m[1][1];
    float f = src->m[1][2];
    float g = src->m[2][0];
    float h = src->m[2][1];
    float i = src->m[2][2];
    float nt0 = -src->m[3][0];
    float nt1 = -src->m[3][1];
    float nt2 = -src->m[3][2];
    float A = e * i - f * h;
    float t0 = i * d - f * g;
    float t1 = h * d - e * g;
    float det = a * A - b * t0 + c * t1;
    float invDet = (det == 0.0f) ? 0.0f : 1.0f / det;
    float negInvDet = -invDet;
    float m00 = A * invDet;
    float m10 = t0 * negInvDet;
    float m20 = t1 * invDet;
    float m01 = (i * b - h * c) * negInvDet;
    float m11 = (a * i - g * c) * invDet;
    float m21 = (a * h - b * g) * negInvDet;
    float m02 = (f * b - e * c) * invDet;
    float m12 = (a * f - d * c) * negInvDet;
    float m22 = (a * e - b * d) * invDet;
    out->m[0][0] = m00;
    out->m[1][0] = m10;
    out->m[2][0] = m20;
    out->m[0][1] = m01;
    out->m[1][1] = m11;
    out->m[2][1] = m21;
    out->m[0][2] = m02;
    out->m[1][2] = m12;
    out->m[2][2] = m22;
    out->m[0][3] = 0.0f;
    out->m[1][3] = 0.0f;
    out->m[2][3] = 0.0f;
    out->m[3][0] = m20 * nt2 + (m00 * nt0 + m10 * nt1);
    out->m[3][1] = m21 * nt2 + (m01 * nt0 + m11 * nt1);
    out->m[3][2] = m22 * nt2 + (m02 * nt0 + m12 * nt1);
    out->m[3][3] = 1.0f;
}
void NuMtxInvH(NUMTX* out, NUMTX const* src) {
    float t01 = src->m[0][0] * src->m[1][1] - src->m[0][1] * src->m[1][0];
    float t02 = src->m[0][0] * src->m[1][2] - src->m[1][0] * src->m[0][2];
    float t03 = src->m[0][0] * src->m[1][3] - src->m[1][0] * src->m[0][3];
    float t12 = src->m[0][1] * src->m[1][2] - src->m[1][1] * src->m[0][2];
    float t13 = src->m[0][1] * src->m[1][3] - src->m[1][1] * src->m[0][3];
    float t23 = src->m[0][2] * src->m[1][3] - src->m[1][2] * src->m[0][3];

    float b01 = src->m[2][0] * src->m[3][1] - src->m[2][1] * src->m[3][0];
    float b02 = src->m[2][0] * src->m[3][2] - src->m[3][0] * src->m[2][2];
    float b03 = src->m[2][0] * src->m[3][3] - src->m[3][0] * src->m[2][3];
    float b12 = src->m[2][1] * src->m[3][2] - src->m[3][1] * src->m[2][2];
    float b13 = src->m[2][1] * src->m[3][3] - src->m[3][1] * src->m[2][3];
    float b23 = src->m[2][2] * src->m[3][3] - src->m[3][2] * src->m[2][3];

    float det = t01 * b23 - t02 * b13 + t03 * b12 + t12 * b03 - t13 * b02 + t23 * b01;
    float invDet = 1.0f / det;

    out->m[0][0] = ((src->m[1][1] * b23 - src->m[1][2] * b13) + src->m[1][3] * b12) * invDet;
    out->m[1][0] = (-(src->m[1][0] * b23) + src->m[1][2] * b03 - src->m[1][3] * b02) * invDet;
    out->m[2][0] = (src->m[1][0] * b13 - src->m[1][1] * b03 + src->m[1][3] * b01) * invDet;
    out->m[3][0] = (src->m[1][1] * b02 - src->m[1][0] * b12 - src->m[1][2] * b01) * invDet;

    out->m[0][1] = (src->m[0][2] * b13 - src->m[0][1] * b23 - src->m[0][3] * b12) * invDet;
    out->m[1][1] = (src->m[0][0] * b23 - src->m[0][2] * b03 + src->m[0][3] * b02) * invDet;
    out->m[2][1] = (src->m[0][1] * b03 - src->m[0][0] * b13 - src->m[0][3] * b01) * invDet;
    out->m[3][1] = (src->m[0][0] * b12 - src->m[0][1] * b02 + src->m[0][2] * b01) * invDet;

    out->m[0][2] = (src->m[3][1] * t23 - src->m[3][2] * t13 + src->m[3][3] * t12) * invDet;
    out->m[1][2] = (-(src->m[3][0] * t23) + src->m[3][2] * t03 - src->m[3][3] * t02) * invDet;
    out->m[2][2] = (src->m[3][0] * t13 - src->m[3][1] * t03 + src->m[3][3] * t01) * invDet;
    out->m[3][2] = (src->m[3][1] * t02 - src->m[3][0] * t12 - src->m[3][2] * t01) * invDet;

    out->m[0][3] = (src->m[2][2] * t13 - src->m[2][1] * t23 - src->m[2][3] * t12) * invDet;
    out->m[1][3] = (src->m[2][0] * t23 - src->m[2][2] * t03 + src->m[2][3] * t02) * invDet;
    out->m[2][3] = (src->m[2][1] * t03 - src->m[2][0] * t13 - src->m[2][3] * t01) * invDet;
    out->m[3][3] = (src->m[2][0] * t12 - src->m[2][1] * t02 + src->m[2][2] * t01) * invDet;
}
void NuMtxInvHOld(NUMTX* out, NUMTX const* src) {
    NUMTX a;
    a.m[0][0] = src->m[0][0];
    a.m[0][1] = src->m[0][1];
    a.m[0][2] = src->m[0][2];
    a.m[0][3] = src->m[0][3];
    a.m[1][0] = src->m[1][0];
    a.m[1][1] = src->m[1][1];
    a.m[1][2] = src->m[1][2];
    a.m[1][3] = src->m[1][3];
    a.m[2][0] = src->m[2][0];
    a.m[2][1] = src->m[2][1];
    a.m[2][2] = src->m[2][2];
    a.m[2][3] = src->m[2][3];
    a.m[3][0] = src->m[3][0];
    a.m[3][1] = src->m[3][1];
    a.m[3][2] = src->m[3][2];
    a.m[3][3] = src->m[3][3];
    int pivot[4];
    for (int i = 0; i < 4; i++) {
        float big = 0.0f;
        pivot[i] = 0;
        for (int j = i; j < 4; j++) {
            float rownorm = 0.0f;
            for (int k = i; k < 4; k++) {
                float v = a.m[j][k];
                rownorm += (v >= 0.0f ? v : -v);
            }
            float av = a.m[j][i];
            av = (av >= 0.0f ? av : -av);
            float scaled = (rownorm * av == 0.0f) ? 0.0f : av / rownorm;
            if (big < scaled) {
                big = scaled;
                pivot[i] = j;
            }
        }
        if (big == 0.0f) {
            return;
        }
        int irow = pivot[i];
        if (irow != i) {
            for (int l = 0; l < 4; l++) {
                float t = a.m[i][l];
                a.m[i][l] = a.m[irow][l];
                a.m[irow][l] = t;
            }
        }
        float piv = a.m[i][i];
        for (int ll = 0; ll < 4; ll++) {
            if (ll != i) {
                a.m[i][ll] = -a.m[i][ll] / piv;
                for (int r = 0; r < 4; r++) {
                    if (r != i) {
                        a.m[r][ll] += a.m[r][i] * a.m[i][ll];
                    }
                }
            }
        }
        for (int r = 0; r < 4; r++) {
            a.m[r][i] = a.m[r][i] / piv;
        }
        a.m[i][i] = 1.0f / piv;
    }
    for (int l = 3; l >= 0; l--) {
        if (pivot[l] != l) {
            for (int k = 0; k < 4; k++) {
                float t = a.m[k][l];
                a.m[k][l] = a.m[k][pivot[l]];
                a.m[k][pivot[l]] = t;
            }
        }
    }
    out->m[0][0] = a.m[0][0];
    out->m[0][1] = a.m[0][1];
    out->m[0][2] = a.m[0][2];
    out->m[0][3] = a.m[0][3];
    out->m[1][0] = a.m[1][0];
    out->m[1][1] = a.m[1][1];
    out->m[1][2] = a.m[1][2];
    out->m[1][3] = a.m[1][3];
    out->m[2][0] = a.m[2][0];
    out->m[2][1] = a.m[2][1];
    out->m[2][2] = a.m[2][2];
    out->m[2][3] = a.m[2][3];
    out->m[3][0] = a.m[3][0];
    out->m[3][1] = a.m[3][1];
    out->m[3][2] = a.m[3][2];
    out->m[3][3] = a.m[3][3];
}
void NuMtxOrth(NUMTX* mtx) {
    float invX
        = 1.0f
          / NuFsqrt(mtx->m[0][0] * mtx->m[0][0] + mtx->m[0][1] * mtx->m[0][1] + mtx->m[0][2] * mtx->m[0][2]);
    mtx->m[0][0] = mtx->m[0][0] * invX;
    mtx->m[0][1] = invX * mtx->m[0][1];
    mtx->m[0][2] = invX * mtx->m[0][2];
    float invY
        = 1.0f
          / NuFsqrt(mtx->m[1][0] * mtx->m[1][0] + mtx->m[1][1] * mtx->m[1][1] + mtx->m[1][2] * mtx->m[1][2]);
    float yx = mtx->m[1][0] * invY;
    float yy = invY * mtx->m[1][1];
    float yz = invY * mtx->m[1][2];
    float zx = mtx->m[0][1] * yz - mtx->m[0][2] * yy;
    float zy = mtx->m[0][2] * yx - mtx->m[0][0] * yz;
    float zz = mtx->m[0][0] * yy - mtx->m[0][1] * yx;
    mtx->m[2][0] = zx;
    mtx->m[2][1] = zy;
    mtx->m[2][2] = zz;
    mtx->m[1][0] = zy * mtx->m[0][2] - zz * mtx->m[0][1];
    mtx->m[1][1] = zz * mtx->m[0][0] - zx * mtx->m[0][2];
    mtx->m[1][2] = zx * mtx->m[0][1] - zy * mtx->m[0][0];
}
NUVEC NuMtxNormalise(NUMTX* out, NUMTX const* src, bool* was_normalised) {
    float len0 = 0.0f;
    float len1 = 0.0f;
    float len2 = 0.0f;
    float lenSq;

    lenSq = src->m[0][0] * src->m[0][0] + src->m[0][1] * src->m[0][1] + src->m[0][2] * src->m[0][2];
    if (!(lenSq <= 0.0f)) {
        len0 = sqrtf(lenSq);
    }
    lenSq = src->m[1][0] * src->m[1][0] + src->m[1][1] * src->m[1][1] + src->m[1][2] * src->m[1][2];
    if (!(lenSq <= 0.0f)) {
        len1 = sqrtf(lenSq);
    }
    lenSq = src->m[2][0] * src->m[2][0] + src->m[2][1] * src->m[2][1] + src->m[2][2] * src->m[2][2];
    if (!(lenSq <= 0.0f)) {
        len2 = sqrtf(lenSq);
    }

    NUVEC r0;
    NUVEC r1;
    NUVEC r2;
    int d0;
    int d1;
    int d2;
    int count = 0;

    if ((len0 >= 0.0f ? len0 : -len0) < 0.001f) {
        d0 = 1;
        count++;
    } else {
        r0.x = src->m[0][0];
        r0.y = src->m[0][1];
        r0.z = src->m[0][2];
        NuVecScale(&r0, &r0, 1.0f / len0);
        d0 = 0;
    }
    if ((len1 >= 0.0f ? len1 : -len1) < 0.001f) {
        d1 = 1;
        count++;
    } else {
        r1.x = src->m[1][0];
        r1.y = src->m[1][1];
        r1.z = src->m[1][2];
        NuVecScale(&r1, &r1, 1.0f / len1);
        d1 = 0;
    }
    if ((len2 >= 0.0f ? len2 : -len2) < 0.001f) {
        d2 = 1;
        count++;
    } else {
        r2.x = src->m[2][0];
        r2.y = src->m[2][1];
        r2.z = src->m[2][2];
        NuVecScale(&r2, &r2, 1.0f / len2);
        d2 = 0;
    }

    if (count >= 2) {
        out->m[0][0] = 0.0f;
        out->m[0][1] = 0.0f;
        out->m[0][2] = 0.0f;
        out->m[1][0] = 0.0f;
        out->m[1][1] = 0.0f;
        out->m[1][2] = 0.0f;
        out->m[2][0] = 0.0f;
        out->m[2][1] = 0.0f;
        out->m[2][2] = 0.0f;
        len0 = 0.0f;
        len1 = 0.0f;
        len2 = 0.0f;
    } else {
        if (count == 0) {
            if (was_normalised) {
                NUVEC tmp;
                NuVecCross(&tmp, &r0, &r1);
                *was_normalised = NuVecDot(&r2, &tmp) > 0.0f;
            }
        } else {
            if (d0) {
                NuVecCross(&r0, &r1, &r2);
            } else if (d1) {
                NuVecCross(&r1, &r2, &r0);
            } else if (d2) {
                NuVecCross(&r2, &r0, &r1);
            }
            if (was_normalised) {
                *was_normalised = true;
            }
        }
        *(NUVEC*)&out->m[0][0] = r0;
        *(NUVEC*)&out->m[1][0] = r1;
        *(NUVEC*)&out->m[2][0] = r2;
    }

    NUVEC result;
    result.x = len0;
    result.y = len1;
    result.z = len2;
    return result;
}
void NuMtxTransposeR(NUMTX* out, NUMTX const* src) {
    float t;
    t = src->m[0][1];
    out->m[0][1] = src->m[1][0];
    out->m[1][0] = t;
    t = src->m[0][2];
    out->m[0][2] = src->m[2][0];
    out->m[2][0] = t;
    t = src->m[1][2];
    out->m[1][2] = src->m[2][1];
    out->m[2][1] = t;
    out->m[0][0] = src->m[0][0];
    out->m[1][1] = src->m[1][1];
    out->m[2][2] = src->m[2][2];
    out->m[3][0] = src->m[3][0];
    out->m[3][1] = src->m[3][1];
    out->m[3][2] = src->m[3][2];
    out->m[3][3] = src->m[3][3];
}
void NuMtxTranspose(NUMTX* out, NUMTX const* src) {
    NUMTX tmp = *src;
    out->m[0][0] = tmp.m[0][0];
    out->m[0][1] = tmp.m[1][0];
    out->m[0][2] = tmp.m[2][0];
    out->m[0][3] = tmp.m[3][0];
    out->m[1][0] = tmp.m[0][1];
    out->m[1][1] = tmp.m[1][1];
    out->m[1][2] = tmp.m[2][1];
    out->m[1][3] = tmp.m[3][1];
    out->m[2][0] = tmp.m[0][2];
    out->m[2][1] = tmp.m[1][2];
    out->m[2][2] = tmp.m[2][2];
    out->m[2][3] = tmp.m[3][2];
    out->m[3][0] = tmp.m[0][3];
    out->m[3][1] = tmp.m[1][3];
    out->m[3][2] = tmp.m[2][3];
    out->m[3][3] = tmp.m[3][3];
}
void NuMtxRotateOld(int angle, float x, float y, float* outX, float* outY) {
    float s = NuSinOld(angle);
    float c = NuSinOld(angle + 16384);
    *outX = c * x - s * y;
    *outY = s * x + c * y;
}
void NuMtxRotateRads(float rads, float x, float y, float* outX, float* outY) {
    float s = NuSinf(rads);
    float c = NuCosf(rads);
    *outX = c * x - s * y;
    *outY = s * x + c * y;
}
void NuMtxVecToEulerXYZOld(NUVEC const* fwd, NUVEC const* up, int* x, int* y, int* z) {
    int az = (int)(NuATan2f(fwd->y, fwd->x) * 10430.3779296875f);
    *z = az;
    float fx, fy;
    NuMtxRotateOld(-az, fwd->x, fwd->y, &fx, &fy);
    float fz = fwd->z;
    float ux, uy;
    NuMtxRotateOld(-*z, up->x, up->y, &ux, &uy);
    float uz = up->z;
    int ay = (int)(NuATan2f(fz, fx) * 10430.3779296875f);
    *y = -ay;
    float ox, uzr;
    NuMtxRotateOld(-ay, ux, uz, &ox, &uzr);
    *x = -(int)(NuATan2f(uy, uzr) * 10430.3779296875f);
}
void NuMtxVecToEulerXYZRads(NUVEC const* fwd, NUVEC const* up, float* x, float* y, float* z) {
    float az = NuATan2f(fwd->y, fwd->x);
    *z = az;
    float fx, fy;
    NuMtxRotateRads(-az, fwd->x, fwd->y, &fx, &fy);
    float fz = fwd->z;
    float ux, uy;
    NuMtxRotateRads(-*z, up->x, up->y, &ux, &uy);
    float uz = up->z;
    float ay = NuATan2f(fz, fx);
    *y = -ay;
    float ox, uzr;
    NuMtxRotateRads(-ay, ux, uz, &ox, &uzr);
    *x = -NuATan2f(uy, uzr);
}
void NuMtxPrint(NUMTX const* mtx) {}
void NuMtxMulVU0(NUMTX* out, NUMTX const* lhs, NUMTX const* rhs) {
    NuMtxMulH(out, lhs, rhs);
}
void NuMtxSetRotateXYZVU0(NUMTX* out, NUANGVEC const* angles) {
    NuMtxSetRotateXYZOld(out, angles);
}
void NuMtxSetRotationXYVU0(NUMTX* out, NUANGVEC const* angles) {
    float cx = NuSinOld(angles->x + 16384);
    float sx = NuSinOld(angles->x);
    float cy = NuSinOld(angles->y + 16384);
    float sy = NuSinOld(angles->y);
    float cz = NuSinOld(16384);
    float sz = NuSinOld(0);
    out->m[0][0] = cy * cz;
    out->m[0][1] = cy * sz;
    out->m[0][2] = -sy;
    out->m[0][3] = 0.0f;
    out->m[1][0] = sx * sy * cz - cx * sz;
    out->m[1][1] = cx * cz + sx * sy * sz;
    out->m[1][2] = sx * cy;
    out->m[1][3] = 0.0f;
    out->m[2][0] = cx * sy * cz + sx * sz;
    out->m[2][1] = cx * sy * sz - sx * cz;
    out->m[2][2] = cx * cy;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
}
