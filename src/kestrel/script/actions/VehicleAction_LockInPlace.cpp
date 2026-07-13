#include "kestrel/script/actions/VehicleAction_LockInPlace.h"

#include <cstdint>

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarBool {
    char pad[0x20];
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarBool* GetVarABS(int id) const;
};

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    void LockPosition(bool value);
};

VehicleAction_LockInPlace::~VehicleAction_LockInPlace() = default;

ActionState VehicleAction_LockInPlace::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    if (pVehicle == nullptr) {
        return ACTION_FINISHED;
    }
    bool value = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value;
    void* pUserData = pVehicle->GetGameUserData();
    if (pUserData == nullptr) {
        return ACTION_FINISHED;
    }
    uintptr_t genericAddr = (uintptr_t)pUserData - 0x10;
    if (genericAddr == 0) {
        return ACTION_FINISHED;
    }
    ApiVehicleUserData_LCGeneric* pGeneric = (ApiVehicleUserData_LCGeneric*)genericAddr;
    pGeneric->LockPosition(value);
    return ACTION_FINISHED;
}
