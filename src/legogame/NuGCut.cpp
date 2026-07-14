#include "numath/types.h"

struct NuCutSceneRaw;
struct NuCutSceneRawLocator;
struct nuanimtime_s;

void NuGCutLocatorCalcMtx_3(NuCutSceneRaw*, NuCutSceneRawLocator*, NUMTX*, float, bool, float*, float*, int*);

void NuGCutLocatorCalcMtx(NuCutSceneRaw* raw, NuCutSceneRawLocator* locator, float f, NUMTX* mtx,
                          nuanimtime_s* time, bool flag, float* a, float* b, int* c) {
    NuGCutLocatorCalcMtx_3(raw, locator, mtx, f, flag, a, b, (int*)b);
}
