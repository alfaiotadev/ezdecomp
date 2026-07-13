#include "kestrel/script/actions/SAction_Function.h"

const char* SAction_Function::GetName() const {
    return m_Name;
}

void SAction_Function::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void SAction_Function::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_Function::Exec(ScriptContext& context) {
    if (m_pFunction != nullptr) {
        m_pFunction(context);
    }
    return ACTION_FINISHED;
}
