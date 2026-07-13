#include "kestrel/script/actions/SAction_SVarSpeechStream_Cue.h"

const char* SAction_SVarSpeechStream_Cue::GetName() const {
    return "SpeechStream_Cue";
}

void SAction_SVarSpeechStream_Cue::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
