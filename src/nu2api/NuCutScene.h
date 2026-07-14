#pragma once

struct instNUGCUTSCENE;
struct NuCutSceneRaw;

void NuSetCutSceneCharacterProcessFn(void (*)(int, instNUGCUTSCENE*, NuCutSceneRaw*, float, int));
