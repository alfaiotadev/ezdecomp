#include "kestrel/script/actions/SAction_AtkMngr_SetInnerCentreAndRadius.h"

const char* SAction_AtkMngr_SetInnerCentreAndRadius::GetName() const {
    return "SetInnerCentreAndRadius";
}

void SAction_AtkMngr_SetInnerCentreAndRadius::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
