#include "kestrel/script/actions/VehicleAction_SetDirection.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    float m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct ApiVehicle {
    void SetRotY(int);
};

ActionState VehicleAction_SetDirection::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    pVehicle->SetRotY((int)context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value);
    return ACTION_FINISHED;
}
