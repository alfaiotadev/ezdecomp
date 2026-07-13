#include "kestrel/script/actions/SAction_GetConversationLengthInSeconds.h"

struct SVarFloat;

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int pad2;
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

class LC_Conversations {
public:
    float GetConversationLengthInSeconds(const char*);
};

extern LC_Conversations* g_pLC_Conversations;

const char* SAction_GetConversationLengthInSeconds::GetName() const {
    return "GetConversationLengthInSeconds";
}
void SAction_GetConversationLengthInSeconds::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_GetConversationLengthInSeconds::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_GetConversationLengthInSeconds::Exec(ScriptContext& context) {
    context.SetReturn<SVarFloat, float>(
        0, g_pLC_Conversations->GetConversationLengthInSeconds(
               context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText));
    return ACTION_FINISHED;
}
