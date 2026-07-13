#include "kestrel/script/actions/SAction_IsBulletBillActive.h"

struct SVarBool;

__attribute__((visibility("hidden"))) bool* g_pBulletBillActive;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_IsBulletBillActive::GetName() const {
    return "IsBulletBillActive";
}
void SAction_IsBulletBillActive::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_IsBulletBillActive::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_IsBulletBillActive::Exec(ScriptContext& context) {
    if (*g_pBulletBillActive) {
        context.SetReturn<SVarBool, bool>(0, true);
    } else {
        context.SetReturn<SVarBool, bool>(0, false);
    }
    return ACTION_FINISHED;
}
