#include "kestrel/script/actions/SAction_UI_StartMission.h"

class JobSystem {
public:
    static int CheckPlayerAffinity(ScriptContext& context, int);
};

class LegoCityHudMission {
public:
    char pad[0xe0];
    void StartMission(unsigned char);
};

extern LegoCityHudMission sMissionHud[] __asm__("_ZN18LegoCityHudMission11sMissionHudE");

const char* SAction_UI_StartMission::GetName() const {
    return "UI_StartMission";
}
void SAction_UI_StartMission::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_StartMission::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_StartMission::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    sMissionHud[player].StartMission(0);
    return ACTION_FINISHED;
}
