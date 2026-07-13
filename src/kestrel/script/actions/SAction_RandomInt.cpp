#include "kestrel/script/actions/SAction_RandomInt.h"

#include "numath/random.h"

struct SVarFloat {
    char pad[0x20];
    float m_Value;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarFloat* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_RandomInt::GetName() const {
    return "RandomInt";
}
void SAction_RandomInt::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
    params.AddParam(SV_NUMBER);
}
void SAction_RandomInt::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_RandomInt::Exec(ScriptContext& context) {
    int min = static_cast<int>(context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_Value);
    int max
        = static_cast<int>(context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value);
    int result = NuRandIntInRange(min, max);
    context.SetReturn<SVarFloat, float>(0, static_cast<float>(result));
    return ACTION_FINISHED;
}
