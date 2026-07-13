#include "kestrel/script/actions/SAction_AILocatorSet.h"

struct AILocatorSetScriptVariable;
struct sDynamicVariableData {
    void* m_pLocator;
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

const char* SAction_AILocatorSet::GetName() const {
    return "LocatorSet";
}
void SAction_AILocatorSet::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
    params.AddParam(SV_WORLD_LEVEL);
}

void SAction_AILocatorSet::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_LOCATOR_SET);
}

ActionState SAction_AILocatorSet::Exec(ScriptContext& context) {
    void* pLocator = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_pHotSpot;
    const char* pText = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    context.SetReturn<AILocatorSetScriptVariable, sDynamicVariableData>(
        0, sDynamicVariableData{pLocator, pText});
    return ACTION_FINISHED;
}
