__attribute__((visibility("hidden"))) void* NuScratchCurrent;

void NuScratchRelease() {
    NuScratchCurrent = ((void**)NuScratchCurrent)[-1];
}
