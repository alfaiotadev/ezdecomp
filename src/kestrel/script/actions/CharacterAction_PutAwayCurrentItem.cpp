#include "kestrel/script/actions/CharacterAction_PutAwayCurrentItem.h"

struct LegoInventoryItem;

class LegoInventory {
public:
    enum eAnimMode {
        // value 2 is used by the original
    };
    void PutItemAway(LegoInventoryItem* pItem, eAnimMode mode, int a, int b, int c, int d);
};

class MechCharacter {
public:
    LegoInventory* GetInventory() const;
};

struct ApiCharacter {
    char pad[181];
    unsigned char flags;
};

ActionState CharacterAction_PutAwayCurrentItem::CharacterExec(ApiCharacter* pCharacter, ScriptContext&) {
    MechCharacter* pMech = nullptr;
    if (pCharacter != nullptr) {
        if ((pCharacter->flags & 0x10) != 0) {
            pMech = (MechCharacter*)((char*)pCharacter - 0x10);
        }
    }
    LegoInventory* pInventory = pMech->GetInventory();
    if (pInventory != nullptr) {
        LegoInventoryItem* pItem = *(LegoInventoryItem**)((char*)pInventory + 56);
        pInventory->PutItemAway(pItem, static_cast<LegoInventory::eAnimMode>(2), 0, 1, 0, 0);
    }
    return ACTION_FINISHED;
}
