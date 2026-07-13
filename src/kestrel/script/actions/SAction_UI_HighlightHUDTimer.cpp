#include "kestrel/script/actions/SAction_UI_HighlightHUDTimer.h"

const char* SAction_UI_HighlightHUDTimer::GetName() const {
    return "UI_HighlightHUDTimer";
}
void SAction_UI_HighlightHUDTimer::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_HighlightHUDTimer::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

class LegoCityHudPlayer {
public:
    void HighlightTimer();
};

extern unsigned int g_pCurrentPlayerIndex;
extern LegoCityHudPlayer* g_pHudPlayerArray[];

ActionState SAction_UI_HighlightHUDTimer::Exec(ScriptContext& context) {
    g_pHudPlayerArray[g_pCurrentPlayerIndex]->HighlightTimer();
    return ACTION_FINISHED;
}
