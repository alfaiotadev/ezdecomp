#include "kestrel/script/actions/CharacterAction_ClearContext.h"

const char* CharacterAction_ClearContext::GetName() const {
    return "Character_ClearContext";
}

class MechCharacter {
public:
    void SystemLevelClearContext();
};

struct ApiCharacter {
    char pad[181];
    unsigned char flags;
};

struct ScriptContext;

ActionState CharacterAction_ClearContext::CharacterExec(ApiCharacter* pCharacter, ScriptContext&) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr) {
        if ((pCharacter->flags & 0x10) != 0) {
            pMech = (MechCharacter*)((char*)pCharacter - 0x10);
        }
    }
    pMech->SystemLevelClearContext();
    return ACTION_FINISHED;
}
