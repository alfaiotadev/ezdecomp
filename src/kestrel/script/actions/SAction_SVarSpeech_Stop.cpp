#include "kestrel/script/actions/SAction_SVarSpeech_Stop.h"

const char* SAction_SVarSpeech_Stop::GetName() const {
    return "Speech_Stop";
}

void SAction_SVarSpeech_Stop::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
