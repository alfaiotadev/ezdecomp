#include "kestrel/script/actions/SAction_RegisterEvent.h"

SAction_RegisterEvent::SAction_RegisterEvent(int inputVariant) {
    m_Signature = 0x7735;
    m_InputVariant = inputVariant;
}

SAction_RegisterEvent::~SAction_RegisterEvent() = default;

const char* SAction_RegisterEvent::GetName() const {
    return "RegisterEvent";
}

void SAction_RegisterEvent::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}

void SAction_RegisterEvent::GetInputs(SCmdParams& params) const {
    params.AddParam(SV_TEXT);
    params.AddParam(SV_HASH);
    for (int i = 0; i < m_InputVariant; i++) {
        params.AddParam(SV_ANY);
    }
}

ActionState SAction_RegisterEvent::Exec(ScriptContext& context) {
    return ACTION_FINISHED;
}
