#include "kestrel/script/actions/SAction_Achievements_ShieldsDone.h"

const char* SAction_Achievements_ShieldsDone::GetName() const {
    return "Achievements_ShieldsDone";
}
void SAction_Achievements_ShieldsDone::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_Achievements_ShieldsDone::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_Achievements_ShieldsDone::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
