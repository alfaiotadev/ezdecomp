#include "kestrel/script/actions/SAction_Text2HotSpot.h"

#include <cstring>

class HotSpot;
struct HotSpotScriptVariable;

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    void* m_pHotSpot;
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

class HotSpotSystem {
public:
    HotSpot* FindHotSpotByName(const char* name) const;
};

using HSS = HotSpotSystem;
extern HSS* g_pHSS __asm__("_ZN12SystemMixinsI13HotSpotSystemE11m_singletonE");

const char* SAction_Text2HotSpot::GetName() const {
    return "HotSpot";
}
void SAction_Text2HotSpot::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_Text2HotSpot::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_HOTSPOT);
}

ActionState SAction_Text2HotSpot::Exec(ScriptContext& context) {
    ScriptVar* pVar = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    const char* pText = pVar->m_pText;
    HotSpot* pHotSpot = nullptr;
    if (pText != nullptr) {
        register int len __asm__("w0") = strlen(pText);
        if (len != 0) {
            pHotSpot = g_pHSS->FindHotSpotByName(pText);
        }
    }
    context.SetReturn<HotSpotScriptVariable, HotSpot*>(0, pHotSpot);
    return ACTION_FINISHED;
}
