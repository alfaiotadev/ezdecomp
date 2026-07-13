#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_AtkMngr_CreateAttackManager : public ActionInstanceData {
public:
    ~SAction_AtkMngr_CreateAttackManager() override;
    const char* GetName() const override;
};
