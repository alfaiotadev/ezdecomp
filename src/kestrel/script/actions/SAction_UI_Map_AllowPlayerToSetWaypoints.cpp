#include "kestrel/script/actions/SAction_UI_Map_AllowPlayerToSetWaypoints.h"

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

static bool* volatile g_pAllowPlayerToSetWaypoints;

const char* SAction_UI_Map_AllowPlayerToSetWaypoints::GetName() const {
    return "UI_Map_AllowPlayerToSetWaypoints";
}
void SAction_UI_Map_AllowPlayerToSetWaypoints::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_UI_Map_AllowPlayerToSetWaypoints::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_Map_AllowPlayerToSetWaypoints::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    ScriptVar* result = context.GetVarABS(p->m_Id);
    bool* ptr = g_pAllowPlayerToSetWaypoints;
    *ptr = result->m_Value;
    return ACTION_FINISHED;
}
