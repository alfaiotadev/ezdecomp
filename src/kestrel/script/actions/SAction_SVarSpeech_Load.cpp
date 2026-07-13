#include "kestrel/script/actions/SAction_SVarSpeech_Load.h"

const char* SAction_SVarSpeech_Load::GetName() const {
    return "Speech_Load";
}

void SAction_SVarSpeech_Load::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
