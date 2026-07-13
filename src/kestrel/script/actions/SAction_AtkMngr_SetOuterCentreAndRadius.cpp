#include "kestrel/script/actions/SAction_AtkMngr_SetOuterCentreAndRadius.h"

const char* SAction_AtkMngr_SetOuterCentreAndRadius::GetName() const {
    return "SetOuterCentreAndRadius";
}

void SAction_AtkMngr_SetOuterCentreAndRadius::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
