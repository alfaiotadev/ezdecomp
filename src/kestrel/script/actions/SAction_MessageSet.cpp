#include "kestrel/script/actions/SAction_MessageSet.h"

struct MessageObject {
    char pad[0x58];
    int m_TextId;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int m_Value;
    char pad2[0x24];
    MessageObject* m_pMessage;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

ActionState SAction_MessageSet::Exec(ScriptContext& context) {
    ScriptVar* pMsgVar = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    MessageObject* pMsg = pMsgVar->m_pMessage;
    ScriptVar* pTextVar = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1);
    pMsg->m_TextId = pTextVar->m_Value;
    return ACTION_FINISHED;
}

const char* SAction_MessageSet::GetName() const {
    return "Message_Set";
}
void SAction_MessageSet::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_MESSAGE);
    params.AddParam(SV_NUMBER);
}
void SAction_MessageSet::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
