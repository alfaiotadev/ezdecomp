#include "kestrel/script/actions/SAction_SVarSpeech_SetDuckingScale.h"

const char* SAction_SVarSpeech_SetDuckingScale::GetName() const {
    return "Speech_SetDuckingScale";
}

void SAction_SVarSpeech_SetDuckingScale::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
