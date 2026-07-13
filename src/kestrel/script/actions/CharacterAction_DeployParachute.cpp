#include "kestrel/script/actions/CharacterAction_DeployParachute.h"

struct ApiCharacter {
    char pad[0xb5];
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
    void DeployParachute();
};

class MechCharacter {
public:
    AddOnListHolder* GetAddOns();
};

ActionState CharacterAction_DeployParachute::CharacterExec(ApiCharacter* pCharacter, ScriptContext&) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr && (pCharacter->flags & 0x10) != 0) {
        pMech = (MechCharacter*)((char*)pCharacter - 0x10);
    }
    SkyDiveAddon* pAddon = pMech->GetAddOns()->Find(SkyDiveAddon::s_HashedAddonName);
    if (pAddon != nullptr) {
        pAddon->DeployParachute();
    }
    return ACTION_FINISHED;
}
