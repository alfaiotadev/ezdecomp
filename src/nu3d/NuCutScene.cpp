struct instNUGCUTSCENE;
struct NuCutSceneRaw;
struct NuANI4AnimRaw;

using NuCutSceneCharacterRenderFn
    = void (*)(int, instNUGCUTSCENE*, NuCutSceneRaw*, float, int, NuANI4AnimRaw*);

extern NuCutSceneCharacterRenderFn NuCutSceneCharacterRender;

void NuSetCutSceneCharacterRenderFn(NuCutSceneCharacterRenderFn fn) {
    NuCutSceneCharacterRender = fn;
}

NuCutSceneCharacterRenderFn NuCutSceneCharacterRender = nullptr;
