#include "kestrel/script/actions/VehicleAction_IsMissionCritical.h"

struct SVarBool;

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    char pad[448];
    unsigned char : 4;
    bool missionCritical : 1;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState VehicleAction_IsMissionCritical::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    context.SetReturn<SVarBool, bool>(0, pGeneric->missionCritical);
    return ACTION_FINISHED;
}
