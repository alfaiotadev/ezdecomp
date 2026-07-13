#pragma once

#include "kestrel/script/actions/CharacterAction.h"

class CharacterAction_MoveTo : public CharacterAction {
public:
    const char* GetName() const override;
};
