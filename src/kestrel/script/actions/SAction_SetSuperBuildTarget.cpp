#include "kestrel/script/actions/SAction_SetSuperBuildTarget.h"

extern volatile int bricktotal_superbuildtarget;

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

class SuperBuildTargetAchieved {
public:
    void StartWaiting();
};

extern SuperBuildTargetAchieved* g_pSuperBuildTarget __asm__("_ZN11LegoCityHud18m_SuperBuildTargetE");

const char* SAction_SetSuperBuildTarget::GetName() const {
    return "SetSuperBuildTarget";
}
void SAction_SetSuperBuildTarget::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_SetSuperBuildTarget::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetSuperBuildTarget::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    bricktotal_superbuildtarget = static_cast<int>(context.GetVarABS(pInput->m_Id)->m_FloatValue);
    g_pSuperBuildTarget->StartWaiting();
    return ACTION_FINISHED;
}
