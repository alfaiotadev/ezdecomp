#include "kestrel/script/actions/SAction_UI_PlayerUsingFastTravel.h"

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

struct FastTravelUI {
    static bool IsActivated(int);
};

const char* SAction_UI_PlayerUsingFastTravel::GetName() const {
    return "UI_PlayerUsingFastTravel";
}
void SAction_UI_PlayerUsingFastTravel::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_PlayerUsingFastTravel::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_UI_PlayerUsingFastTravel::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, FastTravelUI::IsActivated(0));
    return ACTION_FINISHED;
}
