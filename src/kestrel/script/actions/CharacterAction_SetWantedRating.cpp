#include "kestrel/script/actions/CharacterAction_SetWantedRating.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual void Unknown3() = 0;
    char pad[0x48];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

ActionState CharacterAction_SetWantedRating::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1);
    return ACTION_FINISHED;
}
