#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_PickupClusterStudChainStart : public ActionInstanceData {
public:
    ~SAction_PickupClusterStudChainStart() override;
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
};
