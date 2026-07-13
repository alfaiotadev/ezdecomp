#include "kestrel/script/actions/SAction_AtkMngr_SetAllowFinisher.h"

const char* SAction_AtkMngr_SetAllowFinisher::GetName() const {
    return "SetAllowFinishers";
}

void SAction_AtkMngr_SetAllowFinisher::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
