#pragma once

#include "kestrel/script/actions/CharacterAction.h"

class CharacterAction_Kill : public CharacterAction {
public:
    const char* GetName() const override;
};
