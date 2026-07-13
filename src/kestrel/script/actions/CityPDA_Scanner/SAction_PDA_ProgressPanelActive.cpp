#include "kestrel/script/actions/CityPDA_Scanner/SAction_PDA_ProgressPanelActive.h"

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

struct CityPDAState {
    bool progressPanelActive;
};

extern CityPDAState g_CityPDAState;

const char* SAction_PDA_ProgressPanelActive::GetName() const {
    return "PDA_ProgressPanelActive";
}
void SAction_PDA_ProgressPanelActive::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_PDA_ProgressPanelActive::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
ActionState SAction_PDA_ProgressPanelActive::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, g_CityPDAState.progressPanelActive);
    return ACTION_FINISHED;
}
