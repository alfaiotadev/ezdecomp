#include "kestrel/script/actions/SAction_Achievements_MarkChapterComplete.h"

const char* SAction_Achievements_MarkChapterComplete::GetName() const {
    return "Achievements_MarkChapterComplete";
}
void SAction_Achievements_MarkChapterComplete::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_Achievements_MarkChapterComplete::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_Achievements_MarkChapterComplete::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
