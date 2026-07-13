#include "kestrel/script/actions/SAction_CityObjective_IsHidden_TEXT.h"

struct SVarBool;

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
    template <typename T, typename U>
    void SetReturn(int, U);
};

class ScannableObjectiveSystem {
public:
    static bool IsObjectiveHidden(const char* objective);
};

const char* SAction_CityObjective_IsHidden_TEXT::GetName() const {
    return "CityObjective_IsHidden";
}
void SAction_CityObjective_IsHidden_TEXT::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_CityObjective_IsHidden_TEXT::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_CityObjective_IsHidden_TEXT::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    context.SetReturn<SVarBool, bool>(
        0, ScannableObjectiveSystem::IsObjectiveHidden(context.GetVarABS(p->m_Id)->m_String));
    return ACTION_FINISHED;
}
