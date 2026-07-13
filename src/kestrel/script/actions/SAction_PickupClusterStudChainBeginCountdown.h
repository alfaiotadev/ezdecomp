#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_PickupClusterStudChainBeginCountdown : public ActionInstanceData {
public:
    ~SAction_PickupClusterStudChainBeginCountdown() override;
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
};
