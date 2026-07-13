#include "kestrel/script/actions/SAction_SVarSoundListener_SetFocusPositionEnabled.h"

const char* SAction_SVarSoundListener_SetFocusPositionEnabled::GetName() const {
    return "SoundListener_SetFocusPositionEnabled";
}

void SAction_SVarSoundListener_SetFocusPositionEnabled::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
