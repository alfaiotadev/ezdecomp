#include "kestrel/script/actions/SAction_Job_TextToCityObjective.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
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

class SVarCityObjective : public ScriptVar {
public:
    char pad3[0x08];
    const char* m_pText;
    static void ReturnToContext(const char* pText, ScriptContext& context) __asm__(
        "_ZN17SVarCityObjective15ReturnToContextEPKcR13ScriptContexti");
};

const char* SAction_Job_TextToCityObjective::GetName() const {
    return "CityObjective";
}
void SAction_Job_TextToCityObjective::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_Job_TextToCityObjective::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CITY_OBJECTIVE);
}

ActionState SAction_Job_TextToCityObjective::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    SVarCityObjective* pVar = (SVarCityObjective*)context.GetVarABS(pInput->m_Id);
    const char* pText = pVar->m_pText;
    if (pText != nullptr && pText[0] != '\0') {
        SVarCityObjective::ReturnToContext(pText, context);
    } else {
        context.SetReturn<SVarCityObjective, int>(0, -1);
    }
    return ACTION_FINISHED;
}
