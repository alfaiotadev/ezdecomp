#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_SetDefaultRoadGridlockRoadGroup : public ActionInstanceData {
public:
    const char* GetName() const override = 0;
    void GetInputs(SCmdParams& params) const override = 0;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override = 0;

    int GetHashName() const;
};
