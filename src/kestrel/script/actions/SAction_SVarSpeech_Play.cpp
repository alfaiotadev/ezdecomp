#include "kestrel/script/actions/SAction_SVarSpeech_Play.h"

const char* SAction_SVarSpeech_Play::GetName() const {
    return "Speech_Play";
}

void SAction_SVarSpeech_Play::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
