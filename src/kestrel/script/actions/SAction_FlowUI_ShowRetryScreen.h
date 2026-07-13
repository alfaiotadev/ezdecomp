#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

namespace FlowMissionUI {
class SAction_FlowUI_ShowRetryScreen : public ActionInstanceData {
public:
    ~SAction_FlowUI_ShowRetryScreen() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;
};
}  // namespace FlowMissionUI