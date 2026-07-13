#include "kestrel/script/actions/VehicleAction_ReleaseCarriage.h"

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    void ReleaseCarriage();
};

ActionState VehicleAction_ReleaseCarriage::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    pGeneric->ReleaseCarriage();
    return ACTION_FINISHED;
}
