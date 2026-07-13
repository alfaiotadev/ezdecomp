#include "kestrel/script/actions/VehicleAction_GetDirection.h"

struct SVarFloat;

struct ApiVehicle {
    int GetRotY();
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* VehicleAction_GetDirection::GetName() const {
    return "GetDirection";
}

void VehicleAction_GetDirection::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void VehicleAction_GetDirection::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER, "GetDirection");
}

ActionState VehicleAction_GetDirection::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    context.SetReturn<SVarFloat, float>(0, static_cast<float>(pVehicle->GetRotY()));
    return ACTION_FINISHED;
}
