#include "kestrel/script/actions/SAction_UnloadConversationManifest.h"

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

class LC_Conversations {
public:
    void UnLoadConversationManifest(const char*, bool);
};

extern LC_Conversations* g_pLC_Conversations;

const char* SAction_UnloadConversationManifest::GetName() const {
    return "UnloadConversationManifest";
}
void SAction_UnloadConversationManifest::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_UnloadConversationManifest::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UnloadConversationManifest::Exec(ScriptContext& context) {
    g_pLC_Conversations->UnLoadConversationManifest(
        context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText, true);
    return ACTION_FINISHED;
}
