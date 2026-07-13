#include "kestrel/script/actions/SAction_LockCharacterDebug.h"

const char* SAction_LockCharacterDebug::GetName() const {
    return "LockCharacterDebug";
}
void SAction_LockCharacterDebug::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_LockCharacterDebug::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_LockCharacterDebug::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
