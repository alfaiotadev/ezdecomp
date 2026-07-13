#include "kestrel/script/actions/SAction_EnableSkydiveConstantMove.h"

const char* SAction_EnableSkydiveConstantMove::GetName() const {
    return "EnableSkydiveConstantMove";
}

void SAction_EnableSkydiveConstantMove::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
