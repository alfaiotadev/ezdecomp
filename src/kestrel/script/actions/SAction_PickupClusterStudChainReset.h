#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_PickupClusterStudChainReset : public ActionInstanceData {
public:
    ~SAction_PickupClusterStudChainReset() override;
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
};
