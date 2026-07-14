#include "nu2api/nu_mtl.h"

static float* volatile g_pNuMtlAnimateData;

void NuMtlAnimateSetSpeedScale(float scale) {
    *g_pNuMtlAnimateData = scale;
}
