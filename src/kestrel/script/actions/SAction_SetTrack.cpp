#include "kestrel/script/actions/SAction_SetTrack.h"

const char* SAction_SetTrack::GetName() const {
    return "SetTrack";
}

void SAction_SetTrack::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void SAction_SetTrack::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetTrack::Exec(ScriptContext& context) {
    return ACTION_FINISHED;
}
