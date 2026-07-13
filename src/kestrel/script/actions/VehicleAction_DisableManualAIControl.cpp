#include "kestrel/script/actions/VehicleAction_DisableManualAIControl.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
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
    void DisableManualAIControl(bool disabled);
};

ActionState VehicleAction_DisableManualAIControl::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    bool disable = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value;
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    pGeneric->DisableManualAIControl(disable);
    return ACTION_FINISHED;
}
