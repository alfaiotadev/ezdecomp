#include "kestrel/script/actions/SAction_Array_NumberToArray.h"

class SCtxScope;
struct ScriptVariable;

class ScriptArrayObject {
public:
    ScriptArrayObject() : m_pObject(nullptr) {}

    ~ScriptArrayObject() {
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

struct SVarArray;

struct ScriptVariable {
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
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_Array_NumberToArray::GetName() const {
    return "Array";
}
void SAction_Array_NumberToArray::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_Array_NumberToArray::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_ARRAY);
}

ActionState SAction_Array_NumberToArray::Exec(ScriptContext& context) {
    ScriptVariable* pInput = context.m_ppVars[context.m_InputIndex - 1];
    context.GetVarABS(pInput->m_Id);
    ScriptArrayObject object;
    context.SetReturn<SVarArray, ScriptArrayObject>(0, object);
    return ACTION_FINISHED;
}
