#include "kestrel/script/actions/SAction_CityArray_Size.h"

struct SVarCityArrayData {
    char pad[257];
    unsigned char m_Count;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarCityArray {
    char pad[0x0c];
    int m_Type;
    char pad2[0x10];
    SVarCityArrayData* m_pData;
};

struct SVarFloat;

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarCityArray* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_CityArray_Size::GetName() const {
    return "CityArray_Size";
}
void SAction_CityArray_Size::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CITY_ARRAY);
}
void SAction_CityArray_Size::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_CityArray_Size::Exec(ScriptContext& context) {
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    SVarCityArray* array = context.GetVarABS(input->m_Id);
    float size = 0.0f;
    if (array != nullptr) {
        if (array->m_Type == SV_CITY_ARRAY && array->m_pData != nullptr) {
            size = static_cast<float>(array->m_pData->m_Count);
        }
    }
    context.SetReturn<SVarFloat, float>(0, size);
    return ACTION_FINISHED;
}
