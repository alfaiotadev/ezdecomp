#include "kestrel/script/actions/SAction_SetSatNavDestination.h"

const char* SAction_SetSatNavDestination::GetName() const {
    return "Character_SetSatNavDestination";
}

void SAction_SetSatNavDestination::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
