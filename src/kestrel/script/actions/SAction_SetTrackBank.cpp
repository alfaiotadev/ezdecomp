#include "kestrel/script/actions/SAction_SetTrackBank.h"

const char* SAction_SetTrackBank::GetName() const {
    return "SetTrackBank";
}

void SAction_SetTrackBank::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TRACK_BANK);
}

void SAction_SetTrackBank::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetTrackBank::Exec(ScriptContext& context) {
    return ACTION_FINISHED;
}
