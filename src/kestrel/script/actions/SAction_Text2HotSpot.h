#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_Text2HotSpot : public ActionInstanceData {
public:
    ~SAction_Text2HotSpot() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
