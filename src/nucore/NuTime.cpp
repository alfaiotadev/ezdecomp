#include "nucore/NuTime.h"

struct nuapi {
    char _0[0x165C];
    float forceFrameTime;
};

extern struct nuapi nuapi;

void NuTimeForceFrameTime(float f) {
    nuapi.forceFrameTime = f;
}
