#include "kestrel/script/actions/SAction_Job_Break.h"

const char* SAction_Job_Break::GetName() const {
    return "Job_Break";
}
void SAction_Job_Break::GetInputs(SCmdParams& params) const {
    ActionInstanceData::GetInputs(params);
}
void SAction_Job_Break::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_Job_Break::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
