#include "kestrel/script/actions/SAction_EndE3Demo.h"

const char* SAction_EndE3Demo::GetName() const {
    return "EndE3Demo";
}
void SAction_EndE3Demo::GetInputs(SCmdParams& params) const {
    ActionInstanceData::GetInputs(params);
}
void SAction_EndE3Demo::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_EndE3Demo::Exec(ScriptContext& context) {
    return ACTION_UNKNOWN_7;
}
