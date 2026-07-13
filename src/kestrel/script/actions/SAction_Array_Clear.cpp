#include "kestrel/script/actions/SAction_Array_Clear.h"

class ScriptArrayItem {
public:
    virtual ~ScriptArrayItem();
    int m_RefCount;
};

struct ScriptArrayData {
    char pad[0x10];
    void** m_pItems;
    char pad2;
    unsigned char m_Count;
};

class ScriptVar {
public:
    virtual ~ScriptVar();
    char pad1[0x4];
    int m_Type;
    char pad2[0xc];
    int m_Id;
    ScriptArrayData* m_pData;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

const char* SAction_Array_Clear::GetName() const {
    return "Clear";
}
void SAction_Array_Clear::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_ARRAY);
}
void SAction_Array_Clear::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_Array_Clear::Exec(ScriptContext& context) {
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    ScriptVar* array = context.GetVarABS(input->m_Id);
    if (array != nullptr && array->m_Type == SV_ARRAY) {
        ScriptArrayData* data = array->m_pData;
        if (data != nullptr) {
            int count = data->m_Count;
            if (count != 0) {
                int i = 0;
                do {
                    ScriptArrayItem* item = (ScriptArrayItem*)data->m_pItems[i];
                    if (item != nullptr) {
                        if (--item->m_RefCount <= 0) {
                            delete item;
                        }
                    }
                    i++;
                } while (i != count);
            }
            data->m_Count = 0;
        }
    }
    return ACTION_FINISHED;
}
