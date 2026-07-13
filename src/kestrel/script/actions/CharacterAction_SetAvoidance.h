#pragma once

#include "kestrel/script/actions/CharacterAction.h"

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_SetAvoidance : public CharacterAction {
public:
    ActionState CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
};
