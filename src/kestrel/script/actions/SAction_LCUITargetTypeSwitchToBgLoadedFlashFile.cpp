#include "kestrel/script/actions/SAction_LCUITargetTypeSwitchToBgLoadedFlashFile.h"

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

class LCUITargets {
public:
    void SwitchToBgLoadedFlashFile(const char* filename);
};

extern LCUITargets* g_pLCUITargets __asm__("_ZN12SystemMixinsI11LCUITargetsE11m_singletonE");

const char* SAction_LCUITargetTypeSwitchToBgLoadedFlashFile::GetName() const {
    return "LCUITargetTypeSwitchToBgLoadedFlashFile";
}
void SAction_LCUITargetTypeSwitchToBgLoadedFlashFile::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_LCUITargetTypeSwitchToBgLoadedFlashFile::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_LCUITargetTypeSwitchToBgLoadedFlashFile::Exec(ScriptContext& context) {
    LCUITargets* pLCUITargets = g_pLCUITargets;
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    const char* filename = context.GetVarABS(pInput->m_Id)->m_pText;
    pLCUITargets->SwitchToBgLoadedFlashFile(filename);
    return ACTION_FINISHED;
}
