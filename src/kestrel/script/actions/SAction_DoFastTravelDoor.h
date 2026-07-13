#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_DoFastTravelDoor : public ActionInstanceData {
public:
    ~SAction_DoFastTravelDoor() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
