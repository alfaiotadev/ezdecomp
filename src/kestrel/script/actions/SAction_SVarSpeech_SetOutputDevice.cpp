#include "kestrel/script/actions/SAction_SVarSpeech_SetOutputDevice.h"

const char* SAction_SVarSpeech_SetOutputDevice::GetName() const {
    return "Speech_SetOutputDevice";
}

void SAction_SVarSpeech_SetOutputDevice::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
