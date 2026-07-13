#include "kestrel/script/actions/SAction_Array_Size.h"

struct SVarArrayData {
    char pad[25];
    unsigned char m_Count;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarArray {
    char pad[0x0c];
    int m_Type;
    char pad2[0x10];
    SVarArrayData* m_pData;
};

struct SVarFloat;

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarArray* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_Array_Size::GetName() const {
    return "Size";
}
void SAction_Array_Size::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_ARRAY);
}
void SAction_Array_Size::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_Array_Size::Exec(ScriptContext& context) {
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    SVarArray* array = context.GetVarABS(input->m_Id);
    float size = 0.0f;
    if (array != nullptr) {
        if (array->m_Type == SV_ARRAY && array->m_pData != nullptr) {
            size = static_cast<float>(array->m_pData->m_Count);
        }
    }
    context.SetReturn<SVarFloat, float>(0, size);
    return ACTION_FINISHED;
}
