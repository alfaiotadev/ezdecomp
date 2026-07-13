#include "kestrel/script/actions/CharacterAction_SetAvoidance.h"

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

struct AvoidanceData {
    char pad[648];
    int flags;
};

struct ApiCharacter {
    char pad[88];
    AvoidanceData* pData;
};

ActionState CharacterAction_SetAvoidance::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    unsigned char value = context.GetVarABS(p->m_Id + 1)->m_Value;
    AvoidanceData* data = pCharacter->pData;
    int flags = data->flags;
    int set = flags | 0x2;
    int cleared = flags & ~0x2;
    data->flags = (value == 0) ? cleared : set;
    return ACTION_FINISHED;
}
