#include "nu2api/NuSoundSystem.h"

int NuSoundSystem::sAllocdMemory[3];

int NuSound_GetAllocdSampleMemory() {
    return NuSoundSystem::sAllocdMemory[NuSoundSystem::Sample];
}
