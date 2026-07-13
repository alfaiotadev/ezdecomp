#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

struct ScriptContext;

class SAction_Function : public ActionInstanceData {
public:
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState Exec(ScriptContext& context) override;

    const char* m_Name;
    void (*m_pFunction)(ScriptContext&);
};
