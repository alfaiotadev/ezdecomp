#include "kestrel/script/actions/SAction_UI_ReturnToPoliceStationEnabled.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
    char pad2[0x7];
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
    char pad[0x3407];
    bool m_ReturnToPoliceStationEnabled;
};

extern LegoCityGame* g_pLegoCityGame;

const char* SAction_UI_ReturnToPoliceStationEnabled::GetName() const {
    return "UI_ReturnToPoliceStationEnabled";
}
void SAction_UI_ReturnToPoliceStationEnabled::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_UI_ReturnToPoliceStationEnabled::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_ReturnToPoliceStationEnabled::Exec(ScriptContext& context) {
    ScriptVar* pVar = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    if (g_pLegoCityGame != nullptr) {
        g_pLegoCityGame->m_ReturnToPoliceStationEnabled = pVar->m_Value;
    }
    return ACTION_FINISHED;
}
