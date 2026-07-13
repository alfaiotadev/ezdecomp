#pragma once

#include "kestrel/script/actions/CharacterAction.h"

class CharacterAction_Pursue : public CharacterAction {
public:
    const char* GetName() const override;
};
