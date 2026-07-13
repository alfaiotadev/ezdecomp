#include "kestrel/script/actions/VehicleAction_SetUnlimitedBoost.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarFloat {
    char pad[0x20];
    float m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarFloat* GetVarABS(int id) const;
};

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    void SetUnlimitedBoost(float value);
};

ActionState VehicleAction_SetUnlimitedBoost::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    float value = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value;
    pGeneric->SetUnlimitedBoost(value);
    return ACTION_FINISHED;
}
