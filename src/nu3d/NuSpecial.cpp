#include "nu3d/NuSpecial.h"

extern char gNuSpecialLayers[16];

void NuSetLayerVisibility(int layer, bool visible) {
    gNuSpecialLayers[layer] = visible & 1;
}
