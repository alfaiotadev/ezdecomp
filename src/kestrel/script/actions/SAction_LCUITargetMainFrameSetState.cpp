#include "kestrel/script/actions/SAction_LCUITargetMainFrameSetState.h"

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

class LCUITargets {
public:
    void SetUITargetMainFrameState(int state);
};

extern LCUITargets* g_pLCUITargets __asm__("_ZN12SystemMixinsI11LCUITargetsE11m_singletonE");

const char* SAction_LCUITargetMainFrameSetState::GetName() const {
    return "LCUITargetMainFrameSetState";
}
void SAction_LCUITargetMainFrameSetState::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_LCUITargetMainFrameSetState::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_LCUITargetMainFrameSetState::Exec(ScriptContext& context) {
    LCUITargets* pLCUITargets = g_pLCUITargets;
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    int state = static_cast<int>(context.GetVarABS(pInput->m_Id)->m_fValue);
    pLCUITargets->SetUITargetMainFrameState(state);
    return ACTION_FINISHED;
}
