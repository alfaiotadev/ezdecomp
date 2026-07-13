#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_AILocatorSet : public ActionInstanceData {
public:
    ~SAction_AILocatorSet() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
