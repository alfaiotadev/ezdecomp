#include "kestrel/script/actions/SAction_FastTravelStationScript.h"

const char* SAction_FastTravelStationScript::GetName() const {
    return "FastTravelStationScript";
}
void SAction_FastTravelStationScript::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_GIZMO);
}
void SAction_FastTravelStationScript::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_FastTravelStationScript::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
