#include "kestrel/script/actions/SAction_UI_PDA_DisablePlayerInput.h"

const char* SAction_UI_PDA_DisablePlayerInput::GetName() const {
    return "UI_PDA_DisablePlayerInput";
}

void SAction_UI_PDA_DisablePlayerInput::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
