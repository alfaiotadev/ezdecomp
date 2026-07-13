#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_PlayerInsideArea : public ActionInstanceData {
public:
    const char* GetName() const override;
};
