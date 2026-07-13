#include "kestrel/script/actions/SAction_SVarSpeechPack_Load.h"

const char* SAction_SVarSpeechPack_Load::GetName() const {
    return "SpeechPack_Load";
}

void SAction_SVarSpeechPack_Load::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
