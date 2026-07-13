#include "kestrel/script/actions/VehicleAction_IsQueryDismountSet.h"

struct SVarBool;

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    char pad[1474];
    bool queryDismountSet;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState VehicleAction_IsQueryDismountSet::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    context.SetReturn<SVarBool, bool>(0, pGeneric->queryDismountSet);
    return ACTION_FINISHED;
}
