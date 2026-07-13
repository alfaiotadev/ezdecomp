#include "kestrel/script/actions/SAction_SVarSpeechStream_Close.h"

const char* SAction_SVarSpeechStream_Close::GetName() const {
    return "SpeechStream_Close";
}

void SAction_SVarSpeechStream_Close::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
