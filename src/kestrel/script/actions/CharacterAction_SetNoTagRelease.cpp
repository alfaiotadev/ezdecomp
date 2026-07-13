#include "kestrel/script/actions/CharacterAction_SetNoTagRelease.h"

class MechCharacter {
public:
    struct GameData {
        char pad[296];
        unsigned int m_Flags;
    };
    GameData* GetGameData() const;
};

struct ApiCharacter {
    char pad[181];
    unsigned char flags;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarBool {
    char pad[0x20];
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarBool* GetVarABS(int id) const;
};

ActionState CharacterAction_SetNoTagRelease::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr) {
        if ((pCharacter->flags & 0x10) != 0) {
            pMech = (MechCharacter*)((char*)pCharacter - 0x10);
        }
    }
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    SVarBool* pBool = context.GetVarABS(p->m_Id + 1);
    bool value = pBool->m_Value;
    MechCharacter::GameData* pData = pMech->GetGameData();
    if (value == 0) {
        pData->m_Flags &= ~0x8;
    } else {
        pData->m_Flags |= 0x8;
    }
    return ACTION_FINISHED;
}
