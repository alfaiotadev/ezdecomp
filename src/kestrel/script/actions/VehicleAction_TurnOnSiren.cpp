#include "kestrel/script/actions/VehicleAction_TurnOnSiren.h"

#include <cstdint>

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
    char pad2[0x7];
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    void TurnOnSiren(bool);
};

VehicleAction_TurnOnSiren::~VehicleAction_TurnOnSiren() = default;

ActionState VehicleAction_TurnOnSiren::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    if (pUserData == nullptr) {
        return ACTION_FINISHED;
    }
    uintptr_t genericAddr = (uintptr_t)pUserData - 0x10;
    if (genericAddr == 0) {
        return ACTION_FINISHED;
    }
    ApiVehicleUserData_LCGeneric* pGeneric = (ApiVehicleUserData_LCGeneric*)genericAddr;
    pGeneric->TurnOnSiren(context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value);
    return ACTION_FINISHED;
}
