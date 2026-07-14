#include "numath/types.h"

struct NuCutSceneRaw;
struct instNUGCUTSCENE;
struct NuCutSceneRawRigid;
struct instNUGCUTRIGID;

void (*NuCutSceneRigidPostRender)(NuCutSceneRaw&, instNUGCUTSCENE&, NuCutSceneRawRigid&, instNUGCUTRIGID&,
                                  NUMTX&, float);

void NuSetCutSceneRigidPostRenderFn(void (*fn)(NuCutSceneRaw&, instNUGCUTSCENE&, NuCutSceneRawRigid&,
                                               instNUGCUTRIGID&, NUMTX&, float)) {
    NuCutSceneRigidPostRender = fn;
}
