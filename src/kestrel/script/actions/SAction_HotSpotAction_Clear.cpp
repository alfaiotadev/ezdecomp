#include "kestrel/script/actions/SAction_HotSpotAction_Clear.h"

class HotSpot {
public:
    void Clear(bool);
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    char pad2[0x28];
    HotSpot* m_pHotSpot;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

const char* SAction_HotSpotAction_Clear::GetName() const {
    return "HotSpot_Clear";
}
void SAction_HotSpotAction_Clear::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_HOTSPOT);
}
void SAction_HotSpotAction_Clear::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_HotSpotAction_Clear::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    HotSpot* pHotSpot = context.GetVarABS(p->m_Id)->m_pHotSpot;
    if (pHotSpot != nullptr) {
        pHotSpot->Clear(true);
    }
    return ACTION_FINISHED;
}
