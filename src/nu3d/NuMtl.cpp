#include "nu3d/NuMtl.h"

struct NuMtlGlobals {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int currentRenderPlane;
};

__attribute__((visibility("hidden"))) NuMtlGlobals g_NuMtlGlobals;

int NuMtlSetCurrentRenderPlane(int plane) {
    int prev = g_NuMtlGlobals.currentRenderPlane;
    g_NuMtlGlobals.currentRenderPlane = plane;
    return prev;
}
