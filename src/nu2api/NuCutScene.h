#pragma once

struct NuCutSceneRaw;
struct NuANI4AnimRaw;
struct NuCutSceneRawCharExtra;
struct instNUGCUTCHAR_s;

void NuSetCutSceneCharacterDestroyDataFn(void (*fn)(NuCutSceneRaw*, NuANI4AnimRaw*, NuCutSceneRawCharExtra*,
                                                    instNUGCUTCHAR_s*));
