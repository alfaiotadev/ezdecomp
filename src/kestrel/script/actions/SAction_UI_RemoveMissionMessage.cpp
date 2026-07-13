#include "kestrel/script/actions/SAction_UI_RemoveMissionMessage.h"

const char* SAction_UI_RemoveMissionMessage::GetName() const {
    return "UI_RemoveMissionMessage";
}
void SAction_UI_RemoveMissionMessage::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_RemoveMissionMessage::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

class JobSystem {
public:
    static int CheckPlayerAffinity(ScriptContext& context, int);
};

class HudControl {
public:
    void FreeText(unsigned int, unsigned char);
};

class LegoCityHudMission {
public:
    virtual ~LegoCityHudMission();
    virtual void Clear();
    char pad[0x80];
    HudControl* m_pHudControl;
    char pad2[0x50];
};

extern LegoCityHudMission sMissionHud[] __asm__("_ZN18LegoCityHudMission11sMissionHudE");

ActionState SAction_UI_RemoveMissionMessage::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    LegoCityHudMission* hud = &sMissionHud[player];
    HudControl* pControl = hud->m_pHudControl;
    if (pControl != nullptr) {
        pControl->FreeText(3, 0);
    }
    return ACTION_FINISHED;
}
