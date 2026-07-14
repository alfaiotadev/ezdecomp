#include "numath/types.h"

struct NuCutSceneRaw;
struct instNUGCUTSCENE;
struct NuCutSceneRawRigid;
struct instNUGCUTRIGID;

extern void (*NuCutSceneRigidInstUpdate)(NuCutSceneRaw&, instNUGCUTSCENE&, NuCutSceneRawRigid&,
                                         instNUGCUTRIGID&, NUMTX&, float);

void NuSetCutSceneRigidInstUpdateFn(void (*fn)(NuCutSceneRaw&, instNUGCUTSCENE&, NuCutSceneRawRigid&,
                                               instNUGCUTRIGID&, NUMTX&, float)) {
    NuCutSceneRigidInstUpdate = fn;
}
