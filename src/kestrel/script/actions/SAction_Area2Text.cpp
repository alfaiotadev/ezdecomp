#include "kestrel/script/actions/SAction_Area2Text.h"

class ScriptVariable {
public:
    virtual ~ScriptVariable();
    virtual float AsFloat() const;
    virtual int AsInt() const;
    virtual bool AsBool() const;
    virtual const char* AsText() const;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    char pad2[0x28];
    ScriptVariable* m_pScriptVariable;
};

struct SVarText;

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_Area2Text::GetName() const {
    return "Text";
}
void SAction_Area2Text::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_AREA);
}
void SAction_Area2Text::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}

ActionState SAction_Area2Text::Exec(ScriptContext& context) {
    ScriptVariable* pVar
        = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pScriptVariable;
    context.SetReturn<SVarText, const char*>(0, pVar->AsText());
    return ACTION_FINISHED;
}
