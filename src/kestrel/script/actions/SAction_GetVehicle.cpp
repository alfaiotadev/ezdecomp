#include "kestrel/script/actions/SAction_GetVehicle.h"

struct SVarApiVehicle;
struct ApiVehicle;

struct LegacyScriptContext {
    ApiVehicle* GetApiVehicle() const;
};

struct ScriptContext : LegacyScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_GetVehicle::GetName() const {
    return "GetVehicle";
}
void SAction_GetVehicle::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_GetVehicle::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_VEHICLE, "This ApiVehicle");
}
ActionState SAction_GetVehicle::Exec(ScriptContext& context) {
    context.SetReturn<SVarApiVehicle, ApiVehicle*>(0, context.GetApiVehicle());
    return ACTION_FINISHED;
}
