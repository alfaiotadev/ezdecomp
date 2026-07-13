#include "kestrel/script/actions/SAction_StopStudDecayUpdate.h"

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

static bool* volatile g_pStopStudDecayUpdate;

const char* SAction_StopStudDecayUpdate::GetName() const {
    return "StopStudDecayUpdate";
}
void SAction_StopStudDecayUpdate::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_StopStudDecayUpdate::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_StopStudDecayUpdate::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    *g_pStopStudDecayUpdate = !context.GetVarABS(p->m_Id)->m_Value;
    return ACTION_FINISHED;
}
