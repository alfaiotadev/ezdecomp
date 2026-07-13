#include "kestrel/script/actions/SAction_AtkMngr_SetDiffculty.h"

const char* SAction_AtkMngr_SetDiffculty::GetName() const {
    return "SetDifficulty";
}

void SAction_AtkMngr_SetDiffculty::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
