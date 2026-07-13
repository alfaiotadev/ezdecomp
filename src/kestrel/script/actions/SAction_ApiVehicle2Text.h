#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

struct ApiVehicle;
struct ScriptContext;

class SAction_ApiVehicle2Text : public ActionInstanceData {
public:
    ~SAction_ApiVehicle2Text() override;
    const char* GetName() const override;
    void GetInputs(SCmdParams& params) const override;
    void GetOutputs(SCmdParams& params) const override;
    ActionState VehicleExec(ApiVehicle* pVehicle, ScriptContext& context);
};
