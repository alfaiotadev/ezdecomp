#include "kestrel/script/actions/SAction_UI_ShowHUD.h"

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

class LegoCityHud {
public:
    static void SetEnabled(bool enabled);
};

const char* SAction_UI_ShowHUD::GetName() const {
    return "UI_ShowHUD";
}
void SAction_UI_ShowHUD::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_UI_ShowHUD::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_ShowHUD::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    LegoCityHud::SetEnabled(context.GetVarABS(p->m_Id)->m_Value);
    return ACTION_FINISHED;
}
