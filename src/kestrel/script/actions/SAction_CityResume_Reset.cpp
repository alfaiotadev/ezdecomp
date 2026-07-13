#include "kestrel/script/actions/SAction_CityResume_Reset.h"
#include "nucore/NuThreadBase.h"

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

const char* SAction_CityResume_Reset::GetName() const {
    return "CityResume_Reset";
}
void SAction_CityResume_Reset::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_CityResume_Reset::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_CityResume_Reset::Exec(ScriptContext& context) {
    ResumeLocation* pLoc = g_pLegoCityGame->GetResumeLocation();
    pLoc->doorString[0] = '\0';
    pLoc->cutsceneString[0] = '\0';
    pLoc->field_0 = 0;
    pLoc->field_196 = 0;
    NuStrNCpy(pLoc->doorString, "POLICE_LOBBY_EXTERNAL_DOOR", 0x20);
    pLoc->field_192 = 1;
    return ACTION_FINISHED;
}
