#include "kestrel/script/actions/SAction_SetDefaultBoatGridlockRoadGroup.h"

const char* SAction_SetDefaultBoatGridlockRoadGroup::GetName() const {
    return "SetDefaultBoatGridlockRoadGroup";
}

void SAction_SetDefaultBoatGridlockRoadGroup::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

int SAction_SetDefaultBoatGridlockRoadGroup::GetHashName() const {
    return m_InputVariant;
}
