#include "kestrel/script/actions/SAction_UI_PauseHUDTimerDuringMinicut.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;

    ScriptVar* GetVarABS(int id) const;
};

class LegoCityHudPlayer {
public:
    void PauseTimerDuringMinicuts(bool paused);
};

extern unsigned int g_pCurrentPlayerIndex;
extern LegoCityHudPlayer* g_pHudPlayerArray[];

const char* SAction_UI_PauseHUDTimerDuringMinicut::GetName() const {
    return "UI_PauseHUDTimerDuringMinicut";
}
void SAction_UI_PauseHUDTimerDuringMinicut::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_UI_PauseHUDTimerDuringMinicut::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_PauseHUDTimerDuringMinicut::Exec(ScriptContext& context) {
    LegoCityHudPlayer* player = g_pHudPlayerArray[g_pCurrentPlayerIndex];
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    player->PauseTimerDuringMinicuts(context.GetVarABS(p->m_Id)->m_Value);
    return ACTION_FINISHED;
}
