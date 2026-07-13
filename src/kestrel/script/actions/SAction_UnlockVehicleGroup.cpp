#include "kestrel/script/actions/SAction_UnlockVehicleGroup.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    float m_FloatValue;
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class LegoCityGame {
public:
    void SetVehicleGroupLevel(int level);
};

extern LegoCityGame* g_pLegoCityGame;

const char* SAction_UnlockVehicleGroup::GetName() const {
    return "UnlockVehicleGroup";
}
void SAction_UnlockVehicleGroup::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_UnlockVehicleGroup::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UnlockVehicleGroup::Exec(ScriptContext& context) {
    LegoCityGame* pGame = g_pLegoCityGame;
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    ScriptVar* pVar = context.GetVarABS(pInput->m_Id);
    int level = static_cast<int>(pVar->m_FloatValue);
    pGame->SetVehicleGroupLevel(level);
    return ACTION_FINISHED;
}
