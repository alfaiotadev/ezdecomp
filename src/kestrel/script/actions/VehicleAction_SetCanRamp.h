#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

struct ApiVehicle;
struct ScriptContext;

class VehicleAction_SetCanRamp : public ActionInstanceData {
public:
    ~VehicleAction_SetCanRamp() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState VehicleExec(ApiVehicle* pVehicle, ScriptContext& context);
};
