#include "kestrel/script/actions/SAction_SetHotSpot.h"

class HotSpot {
public:
    char pad[0x48];
    void* m_pField72;
    int m_Field80;
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

namespace TaxiUI {
struct HotSpotPosition {
    void* m_pField0;
    int m_Field8;
};
extern HotSpotPosition m_vHotSpotPosition;
extern bool m_bShowHotSpot;
}  // namespace TaxiUI

const char* SAction_SetHotSpot::GetName() const {
    return "SetHotSpot";
}

void SAction_SetHotSpot::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void SAction_SetHotSpot::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetHotSpot::Exec(ScriptContext& context) {
    bool& showHotSpot = TaxiUI::m_bShowHotSpot;
    if (m_InputVariant != 0) {
        HotSpot* pHotSpot = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pHotSpot;
        TaxiUI::m_vHotSpotPosition.m_Field8 = pHotSpot->m_Field80;
        TaxiUI::m_vHotSpotPosition.m_pField0 = pHotSpot->m_pField72;
    }
    showHotSpot = true;
    return ACTION_FINISHED;
}
