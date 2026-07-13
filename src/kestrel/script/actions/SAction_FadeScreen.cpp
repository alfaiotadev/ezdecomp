#include "kestrel/script/actions/SAction_FadeScreen.h"

const char* SAction_FadeScreen::GetName() const {
    return "FadeScreen";
}

void SAction_FadeScreen::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void SAction_FadeScreen::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_FadeScreen::Exec(ScriptContext& context) {
    return ACTION_FINISHED;
}
