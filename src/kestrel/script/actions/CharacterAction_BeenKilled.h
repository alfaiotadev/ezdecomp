#pragma once

#include "kestrel/script/actions/CharacterAction.h"

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_BeenKilled : public CharacterAction {
public:
    ActionState CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
};
