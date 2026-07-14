char gNuSpecialLayers[32] __attribute__((aligned(4096)));

bool NuGetLayerVisibility(int layer) {
    return gNuSpecialLayers[layer] != 0;
}
