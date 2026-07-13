#include "kestrel/script/actions/SAction_UI_ResetMission.h"

const char* SAction_UI_ResetMission::GetName() const {
    return "UI_ResetMission";
}
void SAction_UI_ResetMission::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_ResetMission::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

class JobSystem {
public:
    static int CheckPlayerAffinity(ScriptContext& context, int);
};

class LegoCityHudMission {
public:
    virtual ~LegoCityHudMission();
    virtual void Clear();
    char pad[0xd8];
};

extern LegoCityHudMission sMissionHud[] __asm__("_ZN18LegoCityHudMission11sMissionHudE");

ActionState SAction_UI_ResetMission::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    sMissionHud[player].Clear();
    return ACTION_FINISHED;
}
