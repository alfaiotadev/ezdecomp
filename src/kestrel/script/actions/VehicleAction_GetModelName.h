#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

struct ApiVehicle;
struct ScriptContext;

class VehicleAction_GetModelName : public ActionInstanceData {
public:
    ActionState VehicleExec(ApiVehicle* pVehicle, ScriptContext& context);
};
