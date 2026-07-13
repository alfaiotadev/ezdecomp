#include "kestrel/script/actions/SAction_CityObjective_SetComplete_TEXT.h"

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
    ScriptVar* GetVarABS(int id) const;
};

class ScannableObjectiveSystem {
public:
    static void SetObjectiveComplete(const char* objective);
};

const char* SAction_CityObjective_SetComplete_TEXT::GetName() const {
    return "CityObjective_SetComplete";
}
void SAction_CityObjective_SetComplete_TEXT::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_CityObjective_SetComplete_TEXT::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_CityObjective_SetComplete_TEXT::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    ScannableObjectiveSystem::SetObjectiveComplete(context.GetVarABS(p->m_Id)->m_String);
    return ACTION_FINISHED;
}
