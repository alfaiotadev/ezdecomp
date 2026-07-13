#pragma once

#include "numath/types.h"

int NuLineLineIntersect(NUVEC const* p1, NUVEC const* p2, NUVEC const* p3, NUVEC const* p4, float* mua,
                        float* mub);
int BoundingBoxToLine(NUVEC const* bmin, NUVEC const* bmax, NUMTX const* mtx, NUVEC const* start,
                      NUVEC const* end, float radius, NUVEC* hit);
int NuPlnLine(NUPLANE const* plane, NUVEC const* p1, NUVEC const* p2, NUVEC* intersect);
int NuPlnLine2(NUPLANE const* plane, NUVEC const* p1, NUVEC const* p2, NUVEC const* v1, NUVEC const* v2,
               NUVEC const* v3, NUVEC* intersect, float* t1, float* t2);
int NuPlnLine3(NUPLANE const* plane, NUVEC const* p1, NUVEC* p2, NUVEC* p3, bool* clip);
int NuPlnPlnIntersect(NUPLANE const* p1, NUPLANE const* p2, NUVEC* p_intersect, NUVEC* v_intersect);

// Point Containment and Relationship Tests
int NuPtInPoly(NUVEC const* pt, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3, NUPLANE const* plane);
int NuPtInPolyYZ(NUVEC const* pt, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3);
int NuPtInPolyZY(NUVEC const* pt, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3);
int NuPtInPolyXY(NUVEC const* pt, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3);
int NuPtInPolyYX(NUVEC const* pt, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3);
int NuPtInPolyZX(NUVEC const* pt, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3);
int NuPtInPolyXZ(NUVEC const* pt, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3);
int NuPointRelToBoundingBox(NUVEC const* bmin, NUVEC const* bmax, NUVEC const* pt);

// Distance Queries
float NuLineToPointDistSqr(NUVEC const* p1, NUVEC const* p2, NUVEC const* pt);
float NuLineToPointDistSqrEx(NUVEC const* p1, NUVEC const* p2, NUVEC const* pt, NUVEC* closest);
float NuLineToPointDistSqr_Bounded(NUVEC const* p1, NUVEC const* p2, NUVEC const* pt);
float NuLineToPointDistSqrEx_Bounded(NUVEC const* p1, NUVEC const* p2, NUVEC const* pt, NUVEC* closest);
float NuInfiniteLineToPointDistSqr(NUVEC const* p1, NUVEC const* p2, NUVEC const* pt);
float NuInfiniteLineToPointDistSqrEx(NUVEC const* p1, NUVEC const* p2, NUVEC const* pt, NUVEC* closest);
float NuLineToLineDist(NUVEC* closest1, NUVEC const* p1, NUVEC* closest2, NUVEC const* p2);
float NuPlnDist(NUPLANE const* plane, NUVEC const* pt);
float NuPlnDist2(NUPLANE const* plane, NUVEC const* p1, NUVEC const* p2);

// Clipping and Surface Functions
int NuClipXPlane(NUVEC* out, NUVEC const* p1, NUVEC const* p2, const float* plane);
int NuClipYPlane(NUVEC* out, NUVEC const* p1, NUVEC const* p2, const float* plane);
int NuClipZPlane(NUVEC* out, NUVEC const* p1, NUVEC const* p2, const float* plane);
void NuVecSurfaceNormal(NUVEC* normal, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3);
