#include "kestrel/script/actions/SAction_ApiVehicle.h"

struct SVarApiVehicle;

struct sDynamicVariableData {
    void* m_pVehicle;
    const char* m_pText;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    void* m_pVehicle;
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_ApiVehicle::GetName() const {
    return "Vehicle";
}
void SAction_ApiVehicle::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
    params.AddParam(SV_WORLD_LEVEL);
}
void SAction_ApiVehicle::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_VEHICLE);
}

ActionState SAction_ApiVehicle::Exec(ScriptContext& context) {
    void* pVehicle = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_pVehicle;
    const char* pText = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    context.SetReturn<SVarApiVehicle, sDynamicVariableData>(0, sDynamicVariableData{pVehicle, pText});
    return ACTION_FINISHED;
}
