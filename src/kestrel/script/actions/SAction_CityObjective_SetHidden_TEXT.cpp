#include "kestrel/script/actions/SAction_CityObjective_SetHidden_TEXT.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int pad2;
    const char* m_String;
};

struct SVarBool {
    char pad[0x20];
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class ScannableObjectiveSystem {
public:
    static void SetObjectiveHidden(const char* objective, bool hidden);
};

const char* SAction_CityObjective_SetHidden_TEXT::GetName() const {
    return "CityObjective_SetHidden";
}
void SAction_CityObjective_SetHidden_TEXT::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
    params.AddParam(SV_BOOL);
}
void SAction_CityObjective_SetHidden_TEXT::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_CityObjective_SetHidden_TEXT::Exec(ScriptContext& context) {
    const char* objective = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_String;
    ScannableObjectiveSystem::SetObjectiveHidden(
        objective,
        ((SVarBool*)context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1))->m_Value);
    return ACTION_FINISHED;
}
