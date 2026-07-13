#include "kestrel/script/actions/CharacterAction_SetMoveWithGround.h"

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

struct MoveWithGroundData {
    char pad[256];
    int flags;
};

struct ApiCharacter {
    char pad[464];
    MoveWithGroundData* pData;
};

ActionState CharacterAction_SetMoveWithGround::CharacterExec(ApiCharacter* pCharacter,
                                                             ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    unsigned char value = context.GetVarABS(p->m_Id + 1)->m_Value;
    MoveWithGroundData* data = pCharacter->pData;
    int flags = data->flags;
    int cleared = flags & ~0x1;
    int set = flags | 0x1;
    data->flags = value ? set : cleared;
    return ACTION_FINISHED;
}
