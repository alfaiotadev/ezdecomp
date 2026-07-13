#include "kestrel/script/actions/SAction_UI_HideMissionPrompt.h"

class JobSystem {
public:
    static int CheckPlayerAffinity(ScriptContext& context, int);
};

class LegoCityHudMission {
public:
    virtual ~LegoCityHudMission();
    virtual void Clear();
    virtual void Method2();
    virtual void Method3();
    virtual void Method4();
    virtual void Method5();
    virtual void Method6();
    virtual void SetVisible(bool);
    void HidePrompt();
    char pad[0xd8];
};

extern LegoCityHudMission sMissionHud[] __asm__("_ZN18LegoCityHudMission11sMissionHudE");

const char* SAction_UI_HideMissionPrompt::GetName() const {
    return "UI_HideMissionPrompt";
}
void SAction_UI_HideMissionPrompt::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_HideMissionPrompt::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_HideMissionPrompt::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    LegoCityHudMission* hud = &sMissionHud[player];
    hud->HidePrompt();
    hud->SetVisible(false);
    return ACTION_FINISHED;
}
