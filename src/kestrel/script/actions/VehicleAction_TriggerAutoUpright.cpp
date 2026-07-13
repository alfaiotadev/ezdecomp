#include "kestrel/script/actions/VehicleAction_TriggerAutoUpright.h"

struct ApiVehicle {
    void TriggerDefaultAutoUpright();
};

void VehicleAction_TriggerAutoUpright::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState VehicleAction_TriggerAutoUpright::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    pVehicle->TriggerDefaultAutoUpright();
    return ACTION_FINISHED;
}
