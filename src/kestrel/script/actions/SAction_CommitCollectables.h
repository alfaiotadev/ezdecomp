#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_CommitCollectables : public ActionInstanceData {
public:
    ~SAction_CommitCollectables() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;

    static unsigned int sm_AbilitiesHash;
    static unsigned int sm_AllHash;
    static unsigned int sm_StoryCharHash;
};
