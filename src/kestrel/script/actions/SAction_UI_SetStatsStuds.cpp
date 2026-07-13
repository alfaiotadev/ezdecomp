#include "kestrel/script/actions/SAction_UI_SetStatsStuds.h"

class JobSystem {
public:
    static void CheckPlayerAffinity(ScriptContext& context, int);
};

const char* SAction_UI_SetStatsStuds::GetName() const {
    return "UI_SetStatsStuds";
}
void SAction_UI_SetStatsStuds::GetInputs(SCmdParams& params) const {
    if (m_InputVariant == 0) {
        params.SanityCheck();
    } else if (m_InputVariant == 1) {
        params.SanityCheck();
        params.AddParam(SV_NUMBER);
    }
}
void SAction_UI_SetStatsStuds::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
ActionState SAction_UI_SetStatsStuds::Exec(ScriptContext& context) {
    JobSystem::CheckPlayerAffinity(context, 0);
    return ACTION_FINISHED;
}
