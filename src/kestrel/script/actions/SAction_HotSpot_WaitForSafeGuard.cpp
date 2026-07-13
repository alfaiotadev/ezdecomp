#include "kestrel/script/actions/SAction_HotSpot_WaitForSafeGuard.h"

class HotSpot {
public:
    void SetWaitForSafeGuard(bool);
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    char pad2[0x28];
    HotSpot* m_pHotSpot;
};

struct SVarBool {
    char pad[0x20];
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

const char* SAction_HotSpot_WaitForSafeGuard::GetName() const {
    return "HotSpot_WaitForSafeGuard";
}
void SAction_HotSpot_WaitForSafeGuard::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_HOTSPOT);
    params.AddParam(SV_BOOL);
}
void SAction_HotSpot_WaitForSafeGuard::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_HotSpot_WaitForSafeGuard::Exec(ScriptContext& context) {
    HotSpot* pHotSpot = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pHotSpot;
    if (pHotSpot != nullptr) {
        pHotSpot->SetWaitForSafeGuard(
            ((SVarBool*)context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id))->m_Value);
    }
    return ACTION_FINISHED;
}
