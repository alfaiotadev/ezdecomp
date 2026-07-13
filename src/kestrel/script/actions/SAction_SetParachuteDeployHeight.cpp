#include "kestrel/script/actions/SAction_SetParachuteDeployHeight.h"

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

class SkyDiveAddon {
public:
    static int m_autoParachuteHeight;
};

const char* SAction_SetParachuteDeployHeight::GetName() const {
    return "SetParachuteDeployHeight";
}
void SAction_SetParachuteDeployHeight::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_SetParachuteDeployHeight::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetParachuteDeployHeight::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    SkyDiveAddon::m_autoParachuteHeight = context.GetVarABS(p->m_Id)->m_Value;
    return ACTION_FINISHED;
}
