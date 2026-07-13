#include "kestrel/script/actions/CharacterAction_SetUnEmbed.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    unsigned char m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct UnEmbedData {
    char pad[256];
    int flags;
};

struct ApiCharacter {
    char pad[464];
    UnEmbedData* pData;
};

ActionState CharacterAction_SetUnEmbed::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    UnEmbedData* data = pCharacter->pData;
    unsigned char value = context.GetVarABS(p->m_Id + 1)->m_Value;
    int flags = data->flags;
    int cleared = flags & ~0x2;
    int set = flags | 0x2;
    data->flags = value ? set : cleared;
    return ACTION_FINISHED;
}
