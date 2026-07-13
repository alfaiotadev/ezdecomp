#pragma once

class MechCharacter;

class CharacterPinObject {
    char pad[48];
    MechCharacter* mCharacter;

public:
    MechCharacter* GetCharacter();
};
