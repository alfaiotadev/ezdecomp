#pragma once

struct NuCutSceneRaw;
struct NuANI4AnimRaw;
struct NuCutSceneRawCharExtra;
struct instNUGCUTCHAR_s;
struct nuvariptr_u;
struct LevelContainer;

using NuCutSceneCharacterCreateDataFn = void (*)(NuCutSceneRaw*, NuANI4AnimRaw*, NuCutSceneRawCharExtra*,
                                                 instNUGCUTCHAR_s*, nuvariptr_u*, LevelContainer*, bool);

extern NuCutSceneCharacterCreateDataFn NuCutSceneCharacterCreateData;

void NuSetCutSceneCharacterCreateDataFn(NuCutSceneCharacterCreateDataFn fn);
