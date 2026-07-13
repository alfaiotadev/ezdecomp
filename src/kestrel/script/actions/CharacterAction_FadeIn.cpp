#include "kestrel/script/actions/CharacterAction_FadeIn.h"

struct MechCharacter {
    void FadeIn(float);
};

struct ApiCharacter {
    char pad[181];
    unsigned char flags;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarFloat {
    char pad[0x20];
    float m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarFloat* GetVarABS(int id) const;
};

const char* CharacterAction_FadeIn::GetName() const {
    return "Character_FadeIn";
}

ActionState CharacterAction_FadeIn::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr) {
        if ((pCharacter->flags & 0x10) != 0) {
            pMech = (MechCharacter*)((char*)pCharacter - 0x10);
        }
    }
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    float value = context.GetVarABS(p->m_Id + 1)->m_Value;
    pMech->FadeIn(value);
    return ACTION_FINISHED;
}
