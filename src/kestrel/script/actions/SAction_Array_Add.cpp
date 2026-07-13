#include "kestrel/script/actions/SAction_Array_Add.h"

class SCtxScope;
class ScriptVariable;

class ScriptArrayObject {
public:
    void* m_vtable;
    void Add(ScriptVariable* pItem);
};

class ScriptVariable {
public:
    virtual ~ScriptVariable();
    char pad1[0x4];
    int m_Type;
    char pad2[0xc];
    int m_Id;
    ScriptArrayObject m_Array;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVariable** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVariable* GetVarABS(int id) const;
    ScriptVariable* GetParamVar(int index, SCtxScope* pScope) const;
};

const char* SAction_Array_Add::GetName() const {
    return "Add";
}
void SAction_Array_Add::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_ARRAY);
    params.AddParam(SV_UNKNOWN_1);
}
void SAction_Array_Add::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_Array_Add::Exec(ScriptContext& context) {
    ScriptVariable* pInput = context.m_ppVars[context.m_InputIndex - 1];
    ScriptVariable* pArray = context.GetVarABS(pInput->m_Id);
    if (pArray != nullptr) {
        if (pArray->m_Type == SV_ARRAY) {
            if (pArray->m_Array.m_vtable != nullptr) {
                ScriptVariable* pItem = context.GetParamVar(1, nullptr);
                pArray->m_Array.Add(pItem);
            }
        }
    }
    return ACTION_FINISHED;
}
