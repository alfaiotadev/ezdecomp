#include "kestrel/script/actions/SAction_Achievements_FairgroundRideDone.h"

const char* SAction_Achievements_FairgroundRideDone::GetName() const {
    return "Achievements_FairgroundRideDone";
}
void SAction_Achievements_FairgroundRideDone::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
    params.AddParam(SV_NUMBER);
}
void SAction_Achievements_FairgroundRideDone::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_Achievements_FairgroundRideDone::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
