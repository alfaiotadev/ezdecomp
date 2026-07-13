#pragma once

#include "kestrel/script/actions/CharacterAction.h"

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_GetClass : public CharacterAction {
public:
    const char* GetName() const override;
    ActionState CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
};
