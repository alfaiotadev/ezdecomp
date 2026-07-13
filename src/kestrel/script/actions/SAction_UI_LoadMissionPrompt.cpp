#include "kestrel/script/actions/SAction_UI_LoadMissionPrompt.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int pad2;
    const char* m_String;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class LegoCityHudMission {
public:
    static void LoadPromptResources(const char* resources);
};

const char* SAction_UI_LoadMissionPrompt::GetName() const {
    return "UI_LoadMissionPrompt";
}
void SAction_UI_LoadMissionPrompt::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_UI_LoadMissionPrompt::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_LoadMissionPrompt::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    LegoCityHudMission::LoadPromptResources(context.GetVarABS(p->m_Id)->m_String);
    return ACTION_FINISHED;
}
