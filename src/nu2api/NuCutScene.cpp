#include "numath/types.h"

struct NuCutSceneRaw;
struct NuCutSceneRawLocatorSys;
struct instNUGCUTLOCATOR_s;
struct NuCutSceneRawLocator;

extern void (*NuCutSceneSFXUpdate)(NuCutSceneRaw*, NuCutSceneRawLocatorSys*, instNUGCUTLOCATOR_s*,
                                   NuCutSceneRawLocator*, float, NUMTX*, int);

void NuSetCutSceneSFXUpdateFn(void (*fn)(NuCutSceneRaw*, NuCutSceneRawLocatorSys*, instNUGCUTLOCATOR_s*,
                                         NuCutSceneRawLocator*, float, NUMTX*, int)) {
    NuCutSceneSFXUpdate = fn;
}
