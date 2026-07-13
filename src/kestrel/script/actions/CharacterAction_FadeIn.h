#pragma once

#include "kestrel/script/actions/CharacterAction.h"

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_FadeIn : public CharacterAction {
public:
    const char* GetName() const override;
    ActionState CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
};
