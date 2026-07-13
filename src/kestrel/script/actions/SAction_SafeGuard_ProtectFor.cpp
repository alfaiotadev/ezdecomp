#include "kestrel/script/actions/SAction_SafeGuard_ProtectFor.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    float m_NumberValue;
};

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    char pad[0x48];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct SafeGuard {
    char pad[0x1c];
    float field_1c;
    char field_20;
};

class LegoCityGame {
public:
    static SafeGuard* GetSafeGuard();
};

const char* SAction_SafeGuard_ProtectFor::GetName() const {
    return "SafeGuard_ProtectFor";
}
void SAction_SafeGuard_ProtectFor::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_SafeGuard_ProtectFor::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SafeGuard_ProtectFor::Exec(ScriptContext& context) {
    float input = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_NumberValue;
    SafeGuard* pSafeGuard = LegoCityGame::GetSafeGuard();
    float current = pSafeGuard->field_1c;
    float newValue = current > input ? current : input;
    pSafeGuard->field_20 = 2;
    pSafeGuard->field_1c = newValue;
    return ACTION_FINISHED;
}
