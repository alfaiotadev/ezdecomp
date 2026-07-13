#include "kestrel/script/actions/SAction_SVarSpeech_SetFalloff.h"

const char* SAction_SVarSpeech_SetFalloff::GetName() const {
    return "Speech_SetFalloff";
}

void SAction_SVarSpeech_SetFalloff::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
