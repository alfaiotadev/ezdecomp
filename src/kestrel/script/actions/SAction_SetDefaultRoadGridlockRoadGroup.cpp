#include "kestrel/script/actions/SAction_SetDefaultRoadGridlockRoadGroup.h"

const char* SAction_SetDefaultRoadGridlockRoadGroup::GetName() const {
    return "SetDefaultRoadGridlockRoadGroup";
}

void SAction_SetDefaultRoadGridlockRoadGroup::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

int SAction_SetDefaultRoadGridlockRoadGroup::GetHashName() const {
    return m_InputVariant;
}
