#include "kestrel/script/actions/SAction_PlayerMissedVideoCall.h"

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

struct CityPDA_VideoCallControl {
    static bool WasCallMissed();
};

const char* SAction_PlayerMissedVideoCall::GetName() const {
    return "PlayerMissedVideoCall";
}
void SAction_PlayerMissedVideoCall::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_PlayerMissedVideoCall::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
ActionState SAction_PlayerMissedVideoCall::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, CityPDA_VideoCallControl::WasCallMissed());
    return ACTION_FINISHED;
}
