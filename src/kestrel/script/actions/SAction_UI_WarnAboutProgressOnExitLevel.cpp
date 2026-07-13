#include "kestrel/script/actions/SAction_UI_WarnAboutProgressOnExitLevel.h"

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

static bool* volatile g_pWarnAboutProgressOnExitLevel;

const char* SAction_UI_WarnAboutProgressOnExitLevel::GetName() const {
    return "UI_WarnAboutProgressOnExitLevel";
}
void SAction_UI_WarnAboutProgressOnExitLevel::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_UI_WarnAboutProgressOnExitLevel::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_WarnAboutProgressOnExitLevel::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    *g_pWarnAboutProgressOnExitLevel = context.GetVarABS(p->m_Id)->m_Value;
    return ACTION_FINISHED;
}
