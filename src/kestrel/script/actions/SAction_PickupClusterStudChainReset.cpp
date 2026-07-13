#include "kestrel/script/actions/SAction_PickupClusterStudChainReset.h"

SAction_PickupClusterStudChainReset::~SAction_PickupClusterStudChainReset() = default;

const char* SAction_PickupClusterStudChainReset::GetName() const {
    return "StudChainReset";
}

void SAction_PickupClusterStudChainReset::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
