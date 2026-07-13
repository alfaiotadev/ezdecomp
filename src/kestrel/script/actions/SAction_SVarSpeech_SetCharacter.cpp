#include "kestrel/script/actions/SAction_SVarSpeech_SetCharacter.h"

const char* SAction_SVarSpeech_SetCharacter::GetName() const {
    return "Speech_SetCharacter";
}

void SAction_SVarSpeech_SetCharacter::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
