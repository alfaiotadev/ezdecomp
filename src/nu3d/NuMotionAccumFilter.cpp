#include "nu3d/NuMotionAccumFilter.h"

extern bool g_motionAccumAABoost;

void NuMotionAccumSetAABoost(bool enable) {
    g_motionAccumAABoost = enable;
}
