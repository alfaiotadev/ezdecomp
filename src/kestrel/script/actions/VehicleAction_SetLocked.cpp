#include "kestrel/script/actions/VehicleAction_SetLocked.h"

struct SVarBool;

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

struct VehicleData {
    char pad[52];
    int locked;
};

class ApiVehicleUserData_LCGeneric {
public:
    char pad[24];
    VehicleData* data;
};

VehicleAction_SetLocked::~VehicleAction_SetLocked() = default;

const char* VehicleAction_SetLocked::GetName() const {
    return "SetLocked";
}

void VehicleAction_SetLocked::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL, "Locked");
}

void VehicleAction_SetLocked::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState VehicleAction_SetLocked::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    bool value = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value;
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    if (pGeneric->data != nullptr) {
        if (value) {
            pGeneric->data->locked = -1;
        } else {
            pGeneric->data->locked = 0;
        }
    }
    return ACTION_FINISHED;
}
