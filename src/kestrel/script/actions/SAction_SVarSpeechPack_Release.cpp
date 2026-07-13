#include "kestrel/script/actions/SAction_SVarSpeechPack_Release.h"

const char* SAction_SVarSpeechPack_Release::GetName() const {
    return "SpeechPack_Release";
}

void SAction_SVarSpeechPack_Release::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
