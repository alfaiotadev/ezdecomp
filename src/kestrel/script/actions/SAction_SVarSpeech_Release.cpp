#include "kestrel/script/actions/SAction_SVarSpeech_Release.h"

const char* SAction_SVarSpeech_Release::GetName() const {
    return "Speech_Release";
}

void SAction_SVarSpeech_Release::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
