#include "kestrel/script/actions/SAction_IsStatusScreenActive.h"

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

int GetMenuID();

__attribute__((visibility("hidden"))) int* g_pMenuID;

const char* SAction_IsStatusScreenActive::GetName() const {
    return "IsStatusScreenActive";
}
void SAction_IsStatusScreenActive::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_IsStatusScreenActive::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_IsStatusScreenActive::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, GetMenuID() == *g_pMenuID);
    return ACTION_FINISHED;
}
