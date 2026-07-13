#include "kestrel/script/actions/SAction_AILocator.h"

struct AILocatorScriptVariable;
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

const char* SAction_AILocator::GetName() const {
    return "Locator";
}
void SAction_AILocator::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
    params.AddParam(SV_WORLD_LEVEL);
}

void SAction_AILocator::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_LOCATOR);
}

ActionState SAction_AILocator::Exec(ScriptContext& context) {
    void* pLocator = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_pHotSpot;
    const char* pText = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    context.SetReturn<AILocatorScriptVariable, sDynamicVariableData>(0,
                                                                     sDynamicVariableData{pLocator, pText});
    return ACTION_FINISHED;
}
