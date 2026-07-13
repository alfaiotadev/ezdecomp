#include "kestrel/script/actions/SAction_SetDetectiveFootprint.h"

class Gizmo;

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    char pad2[0x8];
    const char* m_pText;
    char pad3[0x18];
    Gizmo* m_pGizmo;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

void LegoCityObstacles_SetDetectiveFootprint(Gizmo* pGizmo, const char* pText);

const char* SAction_SetDetectiveFootprint::GetName() const {
    return "SetDetectiveFootprint";
}
void SAction_SetDetectiveFootprint::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_GIZMO);
    params.AddParam(SV_TEXT);
}
void SAction_SetDetectiveFootprint::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetDetectiveFootprint::Exec(ScriptContext& context) {
    Gizmo* pGizmo = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pGizmo;
    const char* pText = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_pText;
    LegoCityObstacles_SetDetectiveFootprint(pGizmo, pText);
    return ACTION_FINISHED;
}
