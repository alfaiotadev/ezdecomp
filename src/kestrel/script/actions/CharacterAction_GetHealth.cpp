#include "kestrel/script/actions/CharacterAction_GetHealth.h"

struct MechCharacter {
    char GetHitPoints() const;
};

struct ApiCharacter {
    char pad[181];
    unsigned char flags;
};

struct SVarFloat;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState CharacterAction_GetHealth::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr) {
        if ((pCharacter->flags & 0x10) != 0) {
            pMech = (MechCharacter*)((char*)pCharacter - 0x10);
        }
    }
    context.SetReturn<SVarFloat, float>(0, static_cast<float>(pMech->GetHitPoints()));
    return ACTION_FINISHED;
}
