#include "nu2api/FlashScene.h"

FlashGraph* FlashScene_GetGraph(FlashScene* scene) {
    if (scene != nullptr) {
        return scene->graph;
    }
    return nullptr;
}

void* FlashScene_GetSystem(FlashScene* scene) {
    if (scene != nullptr) {
        return scene->system;
    }
    return nullptr;
}

int FlashScene_GetAnimCount(FlashScene* scene) {
    return scene->animCount;
}
