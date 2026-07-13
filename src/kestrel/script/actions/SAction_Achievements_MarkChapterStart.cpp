#include "kestrel/script/actions/SAction_Achievements_MarkChapterStart.h"

const char* SAction_Achievements_MarkChapterStart::GetName() const {
    return "Achievements_MarkChapterStart";
}
void SAction_Achievements_MarkChapterStart::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_Achievements_MarkChapterStart::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_Achievements_MarkChapterStart::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
