#include "kestrel/script/actions/SAction_UI_GetHUDTimerTime.h"

struct SVarFloat;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_UI_GetHUDTimerTime::GetName() const {
    return "UI_GetHUDTimerTime";
}

void SAction_UI_GetHUDTimerTime::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void SAction_UI_GetHUDTimerTime::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

class LegoCityHudPlayer {
public:
    float GetTimeElapsed() const;
};

extern unsigned int g_pCurrentPlayerIndex;
extern LegoCityHudPlayer* g_pHudPlayerArray[];

ActionState SAction_UI_GetHUDTimerTime::Exec(ScriptContext& context) {
    context.SetReturn<SVarFloat, float>(0, g_pHudPlayerArray[g_pCurrentPlayerIndex]->GetTimeElapsed());
    return ACTION_FINISHED;
}
