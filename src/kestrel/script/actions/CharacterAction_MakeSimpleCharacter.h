#pragma once

#include "kestrel/script/actions/CharacterAction.h"

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_MakeSimpleCharacter : public CharacterAction {
public:
    static bool CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
};
