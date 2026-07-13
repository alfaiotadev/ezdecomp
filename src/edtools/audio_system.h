#pragma once

#include "numath/types.h"

__attribute__((visibility("hidden"))) int* edbitsSfxVol;

int edbitsLookupSoundFX(char* soundName);
void edbitsSetSoundFxVolume(int volume);
void edbitsSoundPlay(NUVEC* position, int param2);
long edbitsGetSoundName(int soundId);
