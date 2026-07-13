#pragma once

#include "kestrel/script/actions/CharacterAction.h"

class CharacterAction_Flee : public CharacterAction {
public:
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
};
