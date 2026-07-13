#include "kestrel/script/actions/VehicleAction_IsSubmerged.h"

struct SVarFloat;

struct ApiVehicle {
    float GetInWater();
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* VehicleAction_IsSubmerged::GetName() const {
    return "IsSubmerged";
}

void VehicleAction_IsSubmerged::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void VehicleAction_IsSubmerged::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER, "IsSubmerged");
}

ActionState VehicleAction_IsSubmerged::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    context.SetReturn<SVarFloat, float>(0, pVehicle->GetInWater());
    return ACTION_FINISHED;
}
