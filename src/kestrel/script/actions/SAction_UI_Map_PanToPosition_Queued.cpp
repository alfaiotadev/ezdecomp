#include "kestrel/script/actions/SAction_UI_Map_PanToPosition_Queued.h"

extern int g_playerCount;

const char* SAction_UI_Map_PanToPosition_Queued::GetName() const {
    return "UI_Map_PanToPosition_Queued";
}

void SAction_UI_Map_PanToPosition_Queued::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_Map_PanToPosition_Queued::Exec(ScriptContext& context) {
    for (int i = 0; i < g_playerCount; i++) {
        PerPlayerExec(context, i);
    }
    return ACTION_FINISHED;
}
