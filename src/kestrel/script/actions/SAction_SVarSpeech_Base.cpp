#include "kestrel/script/actions/SAction_SVarSpeech_Base.h"

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

ActionState SAction_SVarSpeech_Base::Exec(ScriptContext& context) {
    ScriptVar* var = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    return this->DoExec(context, &var->m_Value);
}
