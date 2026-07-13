#include "kestrel/script/actions/SAction_CityResume_SetCutscene.h"
#include "nucore/NuThreadBase.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    char pad2[0x8];
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct ResumeLocation {
    char field_0;
    char pad[0x7f];
    char doorString[0x20];
    char cutsceneString[0x20];
    int field_192;
    char field_196;
};

class LegoCityGame {
public:
    ResumeLocation* GetResumeLocation();
};

extern LegoCityGame* g_pLegoCityGame;

const char* SAction_CityResume_SetCutscene::GetName() const {
    return "CityResume_SetCutscene";
}
void SAction_CityResume_SetCutscene::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_CityResume_SetCutscene::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_CityResume_SetCutscene::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    const char* text = context.GetVarABS(pInput->m_Id)->m_pText;
    ResumeLocation* pLoc = g_pLegoCityGame->GetResumeLocation();
    NuStrNCpy(pLoc->cutsceneString, text, 0x20);
    pLoc->field_192 = 1;
    return ACTION_FINISHED;
}
