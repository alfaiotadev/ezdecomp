#include "kestrel/script/actions/SAction_Message2Text.h"

#include <cstdio>

struct ScriptVariable {
    virtual ~ScriptVariable();
    virtual float AsFloat() const;
    virtual int AsInt() const;
    virtual bool AsBool() const;
    virtual const char* AsText() const;
    char pad[0x50];
    float m_Value;
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

const char* SAction_Message2Text::GetName() const {
    return "Text";
}
void SAction_Message2Text::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_MESSAGE);
}
void SAction_Message2Text::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}

ActionState SAction_Message2Text::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    ScriptVariable* pVar = context.GetVarABS(pInput->m_Id)->m_pScriptVariable;
    char buf[16];
    sprintf(buf, "%f.2", pVar->m_Value);
    context.SetReturn<SVarText, const char*>(0, buf);
    return ACTION_FINISHED;
}
