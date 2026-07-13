#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_PlayerMissedVideoCall : public ActionInstanceData {
public:
    ~SAction_PlayerMissedVideoCall() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};