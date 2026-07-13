#include "kestrel/script/actions/SAction_PickupClusterStudChainBeginCountdown.h"

SAction_PickupClusterStudChainBeginCountdown::~SAction_PickupClusterStudChainBeginCountdown() = default;

const char* SAction_PickupClusterStudChainBeginCountdown::GetName() const {
    return "PickupClusterStudChainBeginCountdown";
}

void SAction_PickupClusterStudChainBeginCountdown::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
