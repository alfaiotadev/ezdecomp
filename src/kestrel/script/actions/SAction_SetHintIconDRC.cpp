#include "kestrel/script/actions/SAction_SetHintIconDRC.h"

class LegoCityHints {
public:
    void SetCurrentHintIcon(short);
};

extern LegoCityHints* g_pLegoCityHints;

const char* SAction_SetHintIconDRC::GetName() const {
    return "SetHintIconDRC";
}
void SAction_SetHintIconDRC::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_SetHintIconDRC::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetHintIconDRC::Exec(ScriptContext& context) {
    g_pLegoCityHints->SetCurrentHintIcon(0x298);
    return ACTION_FINISHED;
}
