#include "kestrel/script/actions/VehicleAction_IsLocked.h"

struct SVarBool;

struct VehicleData {
    char pad[52];
    int locked;
};

class ApiVehicleUserData_LCGeneric {
public:
    char pad[24];
    VehicleData* data;
};

struct ApiVehicle {
    void* GetGameUserData() const;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

VehicleAction_IsLocked::~VehicleAction_IsLocked() = default;

const char* VehicleAction_IsLocked::GetName() const {
    return "IsLocked";
}

void VehicleAction_IsLocked::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void VehicleAction_IsLocked::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER, "IsLocked");
}

ActionState VehicleAction_IsLocked::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    bool isLocked = (pGeneric->data != nullptr) ? (pGeneric->data->locked != 0) : false;
    context.SetReturn<SVarBool, bool>(0, isLocked);
    return ACTION_FINISHED;
}
