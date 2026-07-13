#include "kestrel/script/actions/SAction_UI_SetHeroBarMax.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    float m_fValue;
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
    static void ActivateTrueHeroBar(bool enabled);
    static void SetTrueHeroBarMaximum(unsigned long max);
};

const char* SAction_UI_SetHeroBarMax::GetName() const {
    return "UI_SetHeroBarMax";
}
void SAction_UI_SetHeroBarMax::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_UI_SetHeroBarMax::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_SetHeroBarMax::Exec(ScriptContext& context) {
    LegoCityHud::ActivateTrueHeroBar(true);
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    LegoCityHud::SetTrueHeroBarMaximum(static_cast<unsigned long>(
        static_cast<long>(static_cast<int>(context.GetVarABS(p->m_Id)->m_fValue))));
    return ACTION_FINISHED;
}
