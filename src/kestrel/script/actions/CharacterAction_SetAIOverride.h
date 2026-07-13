#pragma once

#include "kestrel/script/actions/CharacterAction.h"

class CharacterAction_SetAIOverride : public CharacterAction {
public:
    ~CharacterAction_SetAIOverride() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
