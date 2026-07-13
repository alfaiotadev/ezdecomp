#pragma once

#include "legoapi/BoxGeom.h"

class ApiCharacterManager;

class ApiCharacter {
public:
    char pad[360];
    ApiCharacterManager* manager;
    char pad2[56];
    float footX;
    float footY;
    float footZ;
    float footW;

    void UpdateTransforms(bool, bool);
    void SetFootPosition(const NuVector3Base& pos);
    void SetManager(ApiCharacterManager* mgr);
};
