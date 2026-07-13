#include "kestrel/script/actions/SAction_SetHintComplete.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
    char pad2[0x7];
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct HINT_s;
HINT_s* Hint_FindHintByName(const char*, int);
void Hint_SetComplete(HINT_s*, unsigned char);

const char* SAction_SetHintComplete::GetName() const {
    return "SetHintComplete";
}
void SAction_SetHintComplete::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_SetHintComplete::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetHintComplete::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    HINT_s* hint = Hint_FindHintByName(context.GetVarABS(p->m_Id)->m_pText, 0);
    if (hint != nullptr) {
        Hint_SetComplete(hint, 1);
    }
    return ACTION_FINISHED;
}
