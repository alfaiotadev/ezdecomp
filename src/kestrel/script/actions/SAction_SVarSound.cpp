#include "kestrel/script/actions/SAction_SVarSound.h"

const char* SAction_SVarSound::GetName() const {
    return "Sound";
}

void SAction_SVarSound::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void SAction_SVarSound::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SVarSound::Exec(ScriptContext& context) {
    return ACTION_FINISHED;
}
