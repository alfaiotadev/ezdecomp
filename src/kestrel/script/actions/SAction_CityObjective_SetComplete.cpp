#include "kestrel/script/actions/SAction_CityObjective_SetComplete.h"

struct ScriptVar {
    char pad[0x0c];
    int m_Type;
    char pad2[0x0c];
    int m_Id;
};

struct SVarCityObjective : public ScriptVar {
    char pad3[0x04];
    int m_InstanceId;
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class ScannableObjectiveProgress {
public:
    void SetInstanceCompleted(unsigned int instanceId, bool completed);
};

class ScannableObjectiveSystem {
public:
    ScannableObjectiveProgress* GetProgressData();
};

using SOS = ScannableObjectiveSystem;
extern SOS* g_pSOS __asm__("_ZN12SystemMixinsI24ScannableObjectiveSystemE11m_singletonE");

const char* SAction_CityObjective_SetComplete::GetName() const {
    return "CityObjective_SetComplete";
}
void SAction_CityObjective_SetComplete::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CITY_OBJECTIVE);
}
void SAction_CityObjective_SetComplete::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_CityObjective_SetComplete::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    SVarCityObjective* pVar = (SVarCityObjective*)context.GetVarABS(pInput->m_Id);
    SVarCityObjective* pObj = (pVar != nullptr && pVar->m_Type == SV_CITY_OBJECTIVE) ? pVar : nullptr;
    g_pSOS->GetProgressData()->SetInstanceCompleted(pObj->m_InstanceId, true);
    return ACTION_FINISHED;
}
