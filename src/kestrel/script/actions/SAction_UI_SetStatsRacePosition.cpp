#include "kestrel/script/actions/SAction_UI_SetStatsRacePosition.h"

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
    char pad[0x9a];
    unsigned char m_RacePosition;
    char pad2[0x45];
};

extern LegoCityHudMission sMissionHud[] __asm__("_ZN18LegoCityHudMission11sMissionHudE");

const char* SAction_UI_SetStatsRacePosition::GetName() const {
    return "UI_SetStatsRacePosition";
}
void SAction_UI_SetStatsRacePosition::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_UI_SetStatsRacePosition::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_SetStatsRacePosition::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    sMissionHud[player].m_RacePosition = (int)context.GetVarABS(input->m_Id)->m_Value;
    return ACTION_FINISHED;
}
