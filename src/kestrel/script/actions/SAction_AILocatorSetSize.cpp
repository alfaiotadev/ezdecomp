#include "kestrel/script/actions/SAction_AILocatorSetSize.h"

struct SVarFloat;

struct ScriptVariable {
    virtual ~ScriptVariable();
    virtual float AsFloat() const;
    virtual int AsInt() const;
    virtual bool AsBool() const;
    virtual const char* AsText() const;
    char pad[0x78];
    int m_Count;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    char pad2[0x28];
    ScriptVariable* m_pScriptVariable;
};

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual void Unknown3() = 0;
    char pad[0x48];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_AILocatorSetSize::GetName() const {
    return "GetLocatorSetSize";
}
void SAction_AILocatorSetSize::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_LOCATOR_SET);
}

void SAction_AILocatorSetSize::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_AILocatorSetSize::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    ScriptVariable* pLocatorSet = context.GetVarABS(pInput->m_Id)->m_pScriptVariable;
    float size = pLocatorSet ? static_cast<float>(pLocatorSet->m_Count) : 0.0f;
    context.SetReturn<SVarFloat, float>(0, size);
    return ACTION_FINISHED;
}
