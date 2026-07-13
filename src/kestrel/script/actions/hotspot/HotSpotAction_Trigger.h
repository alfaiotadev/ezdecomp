#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class HotSpotAction_Trigger : public ActionInstanceData {
public:
    ~HotSpotAction_Trigger() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
