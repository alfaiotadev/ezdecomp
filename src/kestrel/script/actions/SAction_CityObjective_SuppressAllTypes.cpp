#include "kestrel/script/actions/SAction_CityObjective_SuppressAllTypes.h"

const char* SAction_CityObjective_SuppressAllTypes::GetName() const {
    return "CityObjective_SuppressAllTypes";
}
void SAction_CityObjective_SuppressAllTypes::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_CityObjective_SuppressAllTypes::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

struct SVarBool {
    char pad[0x20];
    unsigned char m_Value;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int pad2;
    const char* m_String;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarBool* GetVarABS(int id) const;
};

class ScannableObjectiveTypeSuppressor {
public:
    void RequestSuppressAll(unsigned long);
    void RequestUnsuppressAll(unsigned long);
};

class ScannableObjectiveSystem {
public:
    ScannableObjectiveTypeSuppressor* GetTypeSuppressor();
};

using SOS = ScannableObjectiveSystem;

extern SOS* g_pSOS __asm__("_ZN12SystemMixinsI24ScannableObjectiveSystemE11m_singletonE");

ActionState SAction_CityObjective_SuppressAllTypes::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    bool suppress = context.GetVarABS(p->m_Id)->m_Value != 0;
    ScannableObjectiveTypeSuppressor* suppressor = g_pSOS->GetTypeSuppressor();
    if (suppress) {
        suppressor->RequestSuppressAll((unsigned long)&context);
    } else {
        suppressor->RequestUnsuppressAll((unsigned long)&context);
    }
    return ACTION_FINISHED;
}
