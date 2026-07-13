#include "kestrel/script/actions/SAction_ConversationManifestPAKIsLoaded.h"

struct SVarBool;

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
    bool ConversationManifestPAKIsLoaded(const char*);
};

extern LC_Conversations* g_pLC_Conversations;

const char* SAction_ConversationManifestPAKIsLoaded::GetName() const {
    return "ConversationManifestPAKIsLoaded";
}
void SAction_ConversationManifestPAKIsLoaded::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_ConversationManifestPAKIsLoaded::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_ConversationManifestPAKIsLoaded::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(
        0, g_pLC_Conversations->ConversationManifestPAKIsLoaded(
               context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText));
    return ACTION_FINISHED;
}
