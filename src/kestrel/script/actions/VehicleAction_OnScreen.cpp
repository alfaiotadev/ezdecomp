#include "kestrel/script/actions/VehicleAction_OnScreen.h"

struct SVarBool;

struct ApiVehicle {
    char pad[3972];
    unsigned int flags;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* VehicleAction_OnScreen::GetName() const {
    return "OnScreen";
}

void VehicleAction_OnScreen::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void VehicleAction_OnScreen::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL, "OnScreen");
}

ActionState VehicleAction_OnScreen::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    bool onScreen = (pVehicle->flags >> 9) & 1;
    context.SetReturn<SVarBool, bool>(0, onScreen);
    return ACTION_FINISHED;
}
