#include "nucore/NuCutScene.h"

void NuCutSceneRawSwap16(void* ptr) {
    char* bytes = (char*)ptr;
    char b0 = bytes[0];
    char b1 = bytes[1];
    bytes[0] = b1;
    bytes[1] = b0;
}
