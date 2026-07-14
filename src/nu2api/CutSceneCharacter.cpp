struct instNUGCUTSCENE;
struct NuCutSceneRaw;
struct instNUGCUTCHAR_s;
struct NuANI4AnimRaw;

extern void (*g_pCutSceneCharacterEvalFn)(instNUGCUTSCENE*, NuCutSceneRaw*, instNUGCUTCHAR_s*, NuANI4AnimRaw*,
                                          float);

void NuSetCutSceneCharacterEvalFn(void (*fn)(instNUGCUTSCENE*, NuCutSceneRaw*, instNUGCUTCHAR_s*,
                                             NuANI4AnimRaw*, float)) {
    g_pCutSceneCharacterEvalFn = fn;
}
