#include "kestrel/script/actions/SAction_UI_IsEndMissionComplete.h"

struct SVarBool;
struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

class JobSystem {
public:
    static int CheckPlayerAffinity(ScriptContext& context, int);
};

class LegoCityHudMission {
public:
    char pad[0x38];
    bool m_EndMissionComplete;
    char pad2[0xa7];
};

extern LegoCityHudMission sMissionHud[] __asm__("_ZN18LegoCityHudMission11sMissionHudE");

const char* SAction_UI_IsEndMissionComplete::GetName() const {
    return "UI_IsEndMissionComplete";
}
void SAction_UI_IsEndMissionComplete::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_IsEndMissionComplete::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_UI_IsEndMissionComplete::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    context.SetReturn<SVarBool, bool>(0, sMissionHud[player].m_EndMissionComplete);
    return ACTION_FINISHED;
}
