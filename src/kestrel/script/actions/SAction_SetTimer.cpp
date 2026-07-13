#include "kestrel/script/actions/SAction_SetTimer.h"

const char* SAction_SetTimer::GetName() const {
    return "Timer_Set";
}

void SAction_SetTimer::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void SAction_SetTimer::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetTimer::Exec(ScriptContext& context) {
    return ACTION_FINISHED;
}
