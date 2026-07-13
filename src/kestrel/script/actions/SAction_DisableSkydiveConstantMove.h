#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_DisableSkydiveConstantMove : public ActionInstanceData {
public:
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
