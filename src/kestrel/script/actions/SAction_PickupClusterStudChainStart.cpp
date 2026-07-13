#include "kestrel/script/actions/SAction_PickupClusterStudChainStart.h"

SAction_PickupClusterStudChainStart::~SAction_PickupClusterStudChainStart() = default;

const char* SAction_PickupClusterStudChainStart::GetName() const {
    return "StudChainStart";
}

void SAction_PickupClusterStudChainStart::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
