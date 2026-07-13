#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class VehicleAction_InArea : public ActionInstanceData {
public:
    const char* GetName() const override;
};
