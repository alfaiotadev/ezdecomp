#include "nu3d/NuPortal.h"

extern int portals_enabled;

int NuPortalEnabled(int enabled) {
    int old = portals_enabled;
    portals_enabled = enabled;
    return old;
}
