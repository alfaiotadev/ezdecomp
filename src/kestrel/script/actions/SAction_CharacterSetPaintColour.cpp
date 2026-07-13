#include "kestrel/script/actions/SAction_CharacterSetPaintColour.h"

const char* SAction_CharacterSetPaintColour::GetName() const {
    return "CharacterSetPaintColour";
}

void SAction_CharacterSetPaintColour::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
