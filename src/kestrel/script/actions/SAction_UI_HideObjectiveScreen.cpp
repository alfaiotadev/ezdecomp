#include "kestrel/script/actions/SAction_UI_HideObjectiveScreen.h"

const char* SAction_UI_HideObjectiveScreen::GetName() const {
    return "UI_HideObjectiveScreen";
}
void SAction_UI_HideObjectiveScreen::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_HideObjectiveScreen::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

struct ObjectiveTracker {
    void ClearObjectives();
};

struct LegoCityGameState {
    char pad[232];
    ObjectiveTracker* objectiveTracker;
};

extern LegoCityGameState* g_pLegoCityGameState;

ActionState SAction_UI_HideObjectiveScreen::Exec(ScriptContext& context) {
    g_pLegoCityGameState->objectiveTracker->ClearObjectives();
    return ACTION_FINISHED;
}
