#include "kestrel/script/actions/SAction_SuppressHints.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

extern int _ZN13LegoCityHints20s_HintSuppressedTimeE __asm__("_ZN13LegoCityHints20s_HintSuppressedTimeE");

const char* SAction_SuppressHints::GetName() const {
    return "SuppressHints";
}
void SAction_SuppressHints::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_SuppressHints::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SuppressHints::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    _ZN13LegoCityHints20s_HintSuppressedTimeE = context.GetVarABS(p->m_Id)->m_Value;
    return ACTION_FINISHED;
}
