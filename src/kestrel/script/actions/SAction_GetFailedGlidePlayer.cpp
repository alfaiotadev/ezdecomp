#include "kestrel/script/actions/SAction_GetFailedGlidePlayer.h"

struct SVarFloat;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

struct GlideRings {
    static int GetLastFailedPlayerIndex();
};

const char* SAction_GetFailedGlidePlayer::GetName() const {
    return "GetFailedGlidePlayer";
}
void SAction_GetFailedGlidePlayer::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_GetFailedGlidePlayer::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
ActionState SAction_GetFailedGlidePlayer::Exec(ScriptContext& context) {
    context.SetReturn<SVarFloat, float>(0, static_cast<float>(GlideRings::GetLastFailedPlayerIndex()));
    return ACTION_FINISHED;
}
