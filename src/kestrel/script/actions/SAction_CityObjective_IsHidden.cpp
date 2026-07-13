#include "kestrel/script/actions/SAction_CityObjective_IsHidden.h"

struct SVarBool;

struct ScriptVar {
    char pad[0x0c];
    int m_Type;
    char pad2[0x0c];
    int m_Id;
};

struct SVarCityObjective : public ScriptVar {
    char pad3[0x04];
    int m_InstanceId;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

class ScannableObjectiveProgress {
public:
    bool IsInstanceHidden(unsigned int instanceId) const;
};

class ScannableObjectiveSystem {
public:
    ScannableObjectiveProgress* GetProgressData();
};

using SOS = ScannableObjectiveSystem;
extern SOS* g_pSOS __asm__("_ZN12SystemMixinsI24ScannableObjectiveSystemE11m_singletonE");

const char* SAction_CityObjective_IsHidden::GetName() const {
    return "CityObjective_IsHidden";
}
void SAction_CityObjective_IsHidden::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CITY_OBJECTIVE);
}
void SAction_CityObjective_IsHidden::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_CityObjective_IsHidden::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    SVarCityObjective* pVar = (SVarCityObjective*)context.GetVarABS(pInput->m_Id);
    SVarCityObjective* pObj = (pVar != nullptr && pVar->m_Type == SV_CITY_OBJECTIVE) ? pVar : nullptr;
    bool hidden = g_pSOS->GetProgressData()->IsInstanceHidden(pObj->m_InstanceId);
    context.SetReturn<SVarBool, bool>(0, hidden);
    return ACTION_FINISHED;
}
