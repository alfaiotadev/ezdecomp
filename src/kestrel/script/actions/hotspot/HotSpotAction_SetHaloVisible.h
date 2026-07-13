#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class HotSpotAction_SetHaloVisible : public ActionInstanceData {
public:
    ~HotSpotAction_SetHaloVisible() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
