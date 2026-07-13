#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_ApiCharacter2Text : public ActionInstanceData {
public:
    const char* GetName() const override;
};
