#include "kestrel/script/actions/SAction_RemoveCriticalFromArea.h"

const char* SAction_RemoveCriticalFromArea::GetName() const {
    return "RemoveCriticalFromArea";
}

void SAction_RemoveCriticalFromArea::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
