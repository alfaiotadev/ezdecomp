#pragma once

#include <numath/types.h>

// Plane Creation
void NuPlnEqn(NUPLANE* result, NUVEC const* v0, NUVEC const* v1, NUVEC const* v2);
void NuPlnEqnPn(NUPLANE* result, NUVEC const* point, NUVEC const* normal);

// Queries & Tests
float NuPlnDist(NUPLANE const* p, NUVEC const* v);
float NuPlnDist2(NUVEC const* plane_point, NUVEC const* plane_normal, NUVEC const* v);

// Intersection
int NuPlnLine(NUPLANE const* p, NUVEC const* start, NUVEC const* end, NUVEC* intersect_point);
int NuPlnLine2(NUPLANE const* p, NUVEC const* v1, NUVEC const* v2, NUVEC const* v3, NUVEC const* v4,
               NUVEC const* v5, NUVEC* intersect_point, float* t1, float* t2);
bool NuPlnLine3(NUPLANE const* p, NUVEC const* line_dir, NUVEC* p0, NUVEC* p1, bool* on_plane);
bool NuPlnPlnIntersect(NUPLANE const* p1, NUPLANE const* p2, NUVEC* line_pt, NUVEC* line_dir);

// Clipping
void NuClipXPlane(NUVEC* result, NUVEC const* v0, NUVEC const* v1, const float* plane_x);
void NuClipYPlane(NUVEC* result, NUVEC const* v0, NUVEC const* v1, const float* plane_y);
void NuClipZPlane(NUVEC* result, NUVEC const* v0, NUVEC const* v1, const float* plane_z);

// SIMD
int NuPlnLineVU0(NUPLANE const* p, NUVEC const* start, NUVEC const* end, NUVEC* intersect_point);
