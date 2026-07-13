#include "kestrel/script/actions/SAction_DisablePursueFromTraffic.h"

const char* SAction_DisablePursueFromTraffic::GetName() const {
    return "DisablePursueFromTraffic";
}

void SAction_DisablePursueFromTraffic::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
