#include "kestrel/script/actions/SAction_UI_StopHUDTimer.h"

const char* SAction_UI_StopHUDTimer::GetName() const {
    return "UI_StopHUDTimer";
}
void SAction_UI_StopHUDTimer::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_StopHUDTimer::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

class LegoCityHudPlayer {
public:
    void StopTimer();
};

extern unsigned int g_pCurrentPlayerIndex;
extern LegoCityHudPlayer* g_pHudPlayerArray[];

ActionState SAction_UI_StopHUDTimer::Exec(ScriptContext& context) {
    g_pHudPlayerArray[g_pCurrentPlayerIndex]->StopTimer();
    return ACTION_FINISHED;
}
