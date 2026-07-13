#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_CharacterInArea : public ActionInstanceData {
public:
    const char* GetName() const override;
};
