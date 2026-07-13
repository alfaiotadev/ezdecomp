#include "kestrel/script/actions/SAction_IsScreenFaded.h"

struct SVarBool;

class FadeSystem {
public:
    float GetFadeTime();
};

struct FadeSystemContainer {
    FadeSystem* m_pFadeSystem;
};

__attribute__((visibility("hidden"))) FadeSystemContainer* g_pFadeSystemContainer;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_IsScreenFaded::GetName() const {
    return "IsScreenFaded";
}
void SAction_IsScreenFaded::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_IsScreenFaded::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_IsScreenFaded::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, g_pFadeSystemContainer->m_pFadeSystem->GetFadeTime() != 0.0f);
    return ACTION_FINISHED;
}
