#include "kestrel/script/actions/SAction_UI_SetStatsIsStoryMission.h"

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

class JobSystem {
public:
    static int CheckPlayerAffinity(ScriptContext& context, int);
};

struct CharProjectFileHelper {
    char pad[0xa1];
    bool isStoryMission;
    char pad2[0x3e];
};

extern CharProjectFileHelper
    g_charProjectFileHelper[2] __asm__("_ZN9SingletonI21CharProjectFileHelperE9mInstanceE");

const char* SAction_UI_SetStatsIsStoryMission::GetName() const {
    return "UI_SetStatsIsStoryMission";
}
void SAction_UI_SetStatsIsStoryMission::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_UI_SetStatsIsStoryMission::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_SetStatsIsStoryMission::Exec(ScriptContext& context) {
    int player = JobSystem::CheckPlayerAffinity(context, 0);
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    bool value = context.GetVarABS(input->m_Id)->m_Value;
    g_charProjectFileHelper[player].isStoryMission = value;
    return ACTION_FINISHED;
}
