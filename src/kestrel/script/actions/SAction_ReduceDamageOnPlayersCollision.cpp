#include "kestrel/script/actions/SAction_ReduceDamageOnPlayersCollision.h"

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

class ApiVehicleUserData_LCGeneric {
public:
    static bool s_reducedDamageOnPlayersCollision;
};

const char* SAction_ReduceDamageOnPlayersCollision::GetName() const {
    return "ReduceDamageOnPlayersCollision";
}
void SAction_ReduceDamageOnPlayersCollision::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_ReduceDamageOnPlayersCollision::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_ReduceDamageOnPlayersCollision::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    ApiVehicleUserData_LCGeneric::s_reducedDamageOnPlayersCollision = context.GetVarABS(p->m_Id)->m_Value;
    return ACTION_FINISHED;
}
