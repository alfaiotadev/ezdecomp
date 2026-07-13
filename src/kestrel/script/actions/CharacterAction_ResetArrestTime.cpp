#include "kestrel/script/actions/CharacterAction_ResetArrestTime.h"

class MechCharacter {
public:
    struct GameData {
        char pad[660];
        float arrestTime;
    };
    GameData* GetGameData() const;
};

struct ApiCharacter {
    char pad[181];
    unsigned char flags;
};

struct ScriptContext;

ActionState CharacterAction_ResetArrestTime::CharacterExec(ApiCharacter* pCharacter, ScriptContext&) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr) {
        if ((pCharacter->flags & 0x10) != 0) {
            pMech = (MechCharacter*)((char*)pCharacter - 0x10);
        }
    }
    pMech->GetGameData()->arrestTime = -1.0f;
    return ACTION_FINISHED;
}
