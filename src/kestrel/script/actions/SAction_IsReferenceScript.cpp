#include "kestrel/script/actions/SAction_IsReferenceScript.h"

struct SVarBool;

struct ScriptContext {
    char _pad[192];
    void* m_pReferenceScript;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_IsReferenceScript::GetName() const {
    return "IsReferenceScript";
}
void SAction_IsReferenceScript::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_IsReferenceScript::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
ActionState SAction_IsReferenceScript::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, context.m_pReferenceScript != nullptr);
    return ACTION_FINISHED;
}
