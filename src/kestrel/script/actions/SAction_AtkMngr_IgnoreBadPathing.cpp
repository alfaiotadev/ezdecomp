#include "kestrel/script/actions/SAction_AtkMngr_IgnoreBadPathing.h"

const char* SAction_AtkMngr_IgnoreBadPathing::GetName() const {
    return "IgnoreBadPathing";
}

void SAction_AtkMngr_IgnoreBadPathing::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
