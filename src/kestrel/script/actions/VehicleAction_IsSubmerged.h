#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

struct ApiVehicle;
struct ScriptContext;

class VehicleAction_IsSubmerged : public ActionInstanceData {
public:
    ~VehicleAction_IsSubmerged() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState VehicleExec(ApiVehicle* pVehicle, ScriptContext& context);
};
