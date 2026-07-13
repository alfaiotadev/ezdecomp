#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_AtkMngr_GetAttackersCount : public ActionInstanceData {
public:
    const char* GetName() const override;
};
