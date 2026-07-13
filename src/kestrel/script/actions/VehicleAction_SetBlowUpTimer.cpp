#include "kestrel/script/actions/VehicleAction_SetBlowUpTimer.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int m_Value;
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
    char pad[1044];
    unsigned char flags;
    char pad2[4716 - 1045];
    int blowUpTimer;
};

ActionState VehicleAction_SetBlowUpTimer::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    if ((pGeneric->flags & 0x2) != 0) {
        pGeneric->blowUpTimer
            = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value;
    }
    return ACTION_FINISHED;
}
