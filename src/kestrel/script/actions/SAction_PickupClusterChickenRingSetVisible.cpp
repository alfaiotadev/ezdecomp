#include "kestrel/script/actions/SAction_PickupClusterChickenRingSetVisible.h"

SAction_PickupClusterChickenRingSetVisible::~SAction_PickupClusterChickenRingSetVisible() = default;

const char* SAction_PickupClusterChickenRingSetVisible::GetName() const {
    return "ChickenRingSetVisible";
}

void SAction_PickupClusterChickenRingSetVisible::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
