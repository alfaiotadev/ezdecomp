#include "kestrel/script/actions/VehicleAction_GetTrailer.h"

struct SVarApiVehicle;
struct ApiVehicle {
    ApiVehicle* GetTrailer();
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* VehicleAction_GetTrailer::GetName() const {
    return "GetTrailer";
}
void VehicleAction_GetTrailer::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void VehicleAction_GetTrailer::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_VEHICLE, "This ApiVehicle");
}

ActionState VehicleAction_GetTrailer::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    context.SetReturn<SVarApiVehicle, ApiVehicle*>(0, pVehicle->GetTrailer());
    return ACTION_FINISHED;
}
