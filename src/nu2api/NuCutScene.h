#pragma once

struct NuCutSceneRaw;

extern void (*NuCutSceneDestroyCharacters)(NuCutSceneRaw*);

void NuSetCutSceneDestroyCharactersFn(void (*fn)(NuCutSceneRaw*));
