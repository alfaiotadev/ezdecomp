#include "kestrel/script/actions/SAction_CityArray_NumberToCityArray.h"

class SCtxScope;
struct ScriptVariable;

class ScriptArrayData {
public:
    ScriptArrayData() : m_pObject(nullptr) {}

    ~ScriptArrayData() {
        if (m_pObject != nullptr) {
            if (--m_pObject->m_RefCount <= 0) {
                delete m_pObject;
            }
            m_pObject = nullptr;
        }
    }

    void Add(ScriptVariable* pItem);

private:
    struct RefCountedBase {
        virtual ~RefCountedBase();
        int m_RefCount;
    };

    RefCountedBase* m_pObject;
};

struct SVarCityArray;

struct ScriptVariable {
public:
    virtual ~ScriptVariable();
    char pad1[0x4];
    int m_Type;
    char pad2[0xc];
    int m_Id;
    ScriptArrayData m_Array;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVariable** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVariable* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_CityArray_NumberToCityArray::GetName() const {
    return "CityArray";
}
void SAction_CityArray_NumberToCityArray::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_CityArray_NumberToCityArray::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CITY_ARRAY);
}

ActionState SAction_CityArray_NumberToCityArray::Exec(ScriptContext& context) {
    ScriptVariable* pInput = context.m_ppVars[context.m_InputIndex - 1];
    context.GetVarABS(pInput->m_Id);
    ScriptArrayData object;
    context.SetReturn<SVarCityArray, ScriptArrayData>(0, object);
    return ACTION_FINISHED;
}
