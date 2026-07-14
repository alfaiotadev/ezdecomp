struct instNUGCUTSCENE;
struct instNUGCUTCHAR_s;
struct NuANI4AnimRaw;
struct NuCutSceneRaw;
struct NuCutSceneRawCharExtra;
struct nuvariptr_u;
struct LevelContainer;

void (*g_pCutSceneCharacterRenderFn)(int, instNUGCUTSCENE*, NuCutSceneRaw*, float, int, NuANI4AnimRaw*);
void (*g_pCutSceneCharacterEvalFn)(instNUGCUTSCENE*, NuCutSceneRaw*, instNUGCUTCHAR_s*, NuANI4AnimRaw*,
                                   float);
void (*g_pCutSceneCharacterReleaseFn)(instNUGCUTCHAR_s*, NuANI4AnimRaw*);
void (*g_pCutSceneCharacterCreateDataFn)(NuCutSceneRaw*, NuANI4AnimRaw*, NuCutSceneRawCharExtra*,
                                         instNUGCUTCHAR_s*, nuvariptr_u*, LevelContainer*, bool);
void (*g_pCutSceneCharacterDestroyDataFn)(NuCutSceneRaw*, NuANI4AnimRaw*, NuCutSceneRawCharExtra*,
                                          instNUGCUTCHAR_s*);

void NuSetCutSceneCharacterRenderFn(void (*param)(int, instNUGCUTSCENE*, NuCutSceneRaw*, float, int,
                                                  NuANI4AnimRaw*)) {
    g_pCutSceneCharacterRenderFn = param;
}

void NuSetCutSceneCharacterEvalFn(void (*param)(instNUGCUTSCENE*, NuCutSceneRaw*, instNUGCUTCHAR_s*,
                                                NuANI4AnimRaw*, float)) {
    g_pCutSceneCharacterEvalFn = param;
}

void NuSetCutSceneCharacterReleaseFn(void (*param)(instNUGCUTCHAR_s*, NuANI4AnimRaw*)) {
    g_pCutSceneCharacterReleaseFn = param;
}

void NuSetCutSceneCharacterCreateDataFn(void (*param)(NuCutSceneRaw*, NuANI4AnimRaw*, NuCutSceneRawCharExtra*,
                                                      instNUGCUTCHAR_s*, nuvariptr_u*, LevelContainer*,
                                                      bool)) {
    g_pCutSceneCharacterCreateDataFn = param;
}

void NuSetCutSceneCharacterDestroyDataFn(void (*param)(NuCutSceneRaw*, NuANI4AnimRaw*,
                                                       NuCutSceneRawCharExtra*, instNUGCUTCHAR_s*)) {
    g_pCutSceneCharacterDestroyDataFn = param;
}
