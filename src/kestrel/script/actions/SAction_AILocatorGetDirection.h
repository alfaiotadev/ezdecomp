#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class AIConvexLocator;

class SAction_AILocatorGetDirection : public ActionInstanceData {
public:
    ~SAction_AILocatorGetDirection() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState LocatorExec(ScriptContext& context, AIConvexLocator* locator);
};
