#include "kestrel/script/actions/CharacterAction_IsSkydiving.h"

struct ApiCharacter {
    char pad[181];
    unsigned char flags;
};

struct HashedKey;

class AddOnListHolder {
public:
    class SkyDiveAddon* Find(const HashedKey& key) const;
};

class SkyDiveAddon {
public:
    static const HashedKey s_HashedAddonName;
};

class MechCharacter {
public:
    AddOnListHolder* GetAddOns();
};

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState CharacterAction_IsSkydiving::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr && (pCharacter->flags & 0x10) != 0) {
        pMech = (MechCharacter*)((char*)pCharacter - 0x10);
    }
    SkyDiveAddon* pAddon = pMech->GetAddOns()->Find(SkyDiveAddon::s_HashedAddonName);
    context.SetReturn<SVarBool, bool>(0, pAddon != nullptr);
    return ACTION_FINISHED;
}
