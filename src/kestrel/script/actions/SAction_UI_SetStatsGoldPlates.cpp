#include "kestrel/script/actions/SAction_UI_SetStatsGoldPlates.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarFloat {
    char pad[0x20];
    float m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarFloat* GetVarABS(int id) const;
};

class JobSystem {
public:
    static int CheckPlayerAffinity(ScriptContext& context, int);
};

class LegoCityHudMission {
public:
    char pad[0x98];
    unsigned char field_0x98;
    unsigned char field_0x99;
    char pad2[0x46];
};

extern LegoCityHudMission sMissionHud[] __asm__("_ZN18LegoCityHudMission11sMissionHudE");

const char* SAction_UI_SetStatsGoldPlates::GetName() const {
    return "UI_SetStatsGoldPlates";
}
void SAction_UI_SetStatsGoldPlates::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_UI_SetStatsGoldPlates::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_SetStatsGoldPlates::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    sMissionHud[player].field_0x98 = 0;
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    sMissionHud[player].field_0x99 = (int)context.GetVarABS(input->m_Id)->m_Value;
    return ACTION_FINISHED;
}
