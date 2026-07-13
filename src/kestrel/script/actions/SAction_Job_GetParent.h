#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_Job_GetParent : public ActionInstanceData {
public:
    ~SAction_Job_GetParent() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
