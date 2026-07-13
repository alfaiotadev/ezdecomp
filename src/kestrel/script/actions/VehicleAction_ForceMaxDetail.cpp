#include "kestrel/script/actions/VehicleAction_ForceMaxDetail.h"

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
    char pad[3972];
    unsigned int flags;
    unsigned char flags2;
};

VehicleAction_ForceMaxDetail::~VehicleAction_ForceMaxDetail() = default;

const char* VehicleAction_ForceMaxDetail::GetName() const {
    return "ForceMaxDetail";
}

void VehicleAction_ForceMaxDetail::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL, "ForceMaxDetail");
}

void VehicleAction_ForceMaxDetail::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState VehicleAction_ForceMaxDetail::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    bool value = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value;
    unsigned long long combined = ((unsigned long long)pVehicle->flags2 << 32) | pVehicle->flags;
    if (value) {
        combined |= 0x20000000ULL;
    } else {
        combined &= ~0x20000000ULL;
    }
    pVehicle->flags = (unsigned int)combined;
    pVehicle->flags2 = (unsigned char)(combined >> 32);
    return ACTION_FINISHED;
}
