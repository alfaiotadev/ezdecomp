struct instNUGCUTSCENE;

extern void (*NuCutSceneRequestSFX)(instNUGCUTSCENE*);

void NuSetCutSceneRequestSFXFn(void (*fn)(instNUGCUTSCENE*)) {
    NuCutSceneRequestSFX = fn;
}
