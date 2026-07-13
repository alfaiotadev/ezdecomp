#pragma once

#include "kestrel/script/actions/CharacterAction.h"

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_ClearVehicle : public CharacterAction {
public:
    void GetOutputs(SCmdParams& params) const override;
    ActionState CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
};
