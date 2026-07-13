#include "legogame/ApiCharacter.h"

void ApiCharacter::SetFootPosition(const NuVector3Base& pos) {
    footX = pos.x;
    footY = pos.y;
    footZ = pos.z;
    footW = 1.0f;
    return UpdateTransforms(true, true);
}

void ApiCharacter::SetManager(ApiCharacterManager* mgr) {
    manager = mgr;
}
