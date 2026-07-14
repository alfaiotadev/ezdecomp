#include "numath/types.h"

struct NuPerfOverridePlayerContext {
    NUVEC cameraPos;
};

void NuPerfOverrideSetCameraPos(NuPerfOverridePlayerContext* context, NUVEC const& pos) {
    context->cameraPos = pos;
}
