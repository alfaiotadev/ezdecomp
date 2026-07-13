#include "kestrel/script/actions/CharacterAction_SetAvoidVehicle.h"

enum GAMEOBJFLAG {
    GAMEOBJFLAG_AVOID_VEHICLE = 0x4d,
    GAMEOBJFLAG_AVOID_VEHICLE2 = 0x75,
};

class cGameObjFlags {
public:
    enum Priority : int {
        DEFAULT = 0,
    };
};

class MechCharacter {
public:
    void SetGameFlag(GAMEOBJFLAG flag, bool value, const cGameObjFlags::Priority& priority);
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

ActionState CharacterAction_SetAvoidVehicle::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr) {
        if ((pCharacter->flags & 0x10) != 0) {
            pMech = (MechCharacter*)((char*)pCharacter - 0x10);
        }
    }
    if (pMech == nullptr) {
        return ACTION_FINISHED;
    }
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    SVarBool* pBool = context.GetVarABS(p->m_Id + 1);
    bool value = !pBool->m_Value;
    pMech->SetGameFlag(GAMEOBJFLAG_AVOID_VEHICLE, value, cGameObjFlags::Priority::DEFAULT);
    pMech->SetGameFlag(GAMEOBJFLAG_AVOID_VEHICLE2, value, cGameObjFlags::Priority::DEFAULT);
    return ACTION_FINISHED;
}
