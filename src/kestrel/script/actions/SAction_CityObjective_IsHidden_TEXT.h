#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_CityObjective_IsHidden_TEXT : public ActionInstanceData {
public:
    ~SAction_CityObjective_IsHidden_TEXT() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
