#include "kestrel/script/actions/SAction_UI_Timer_SetLoudTick.h"

const char* SAction_UI_Timer_SetLoudTick::GetName() const {
    return "UI_Timer_SetLoudTick";
}
void SAction_UI_Timer_SetLoudTick::GetInputs(SCmdParams& params) const {
    if (m_InputVariant == 1) {
        params.AddParam(SV_BOOL);
    } else if (m_InputVariant == 0) {
        params.AddParam(SV_BOOL);
        params.AddParam(SV_NUMBER);
    }
}
void SAction_UI_Timer_SetLoudTick::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
