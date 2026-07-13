#include "kestrel/script/actions/SAction_HotSpot.h"

struct HotSpotScriptVariable;
struct sDynamicVariableData {
    void* m_pHotSpot;
    const char* m_pText;
};

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

const char* SAction_HotSpot::GetName() const {
    return "HotSpot";
}
void SAction_HotSpot::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
    params.AddParam(SV_WORLD_LEVEL);
}
void SAction_HotSpot::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_HOTSPOT);
}

ActionState SAction_HotSpot::Exec(ScriptContext& context) {
    void* pHotSpot = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_pHotSpot;
    const char* pText = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    context.SetReturn<HotSpotScriptVariable, sDynamicVariableData>(0, sDynamicVariableData{pHotSpot, pText});
    return ACTION_FINISHED;
}
