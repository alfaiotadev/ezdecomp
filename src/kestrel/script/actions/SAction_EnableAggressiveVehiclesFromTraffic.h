#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_EnableAggressiveVehiclesFromTraffic : public ActionInstanceData {
public:
    ~SAction_EnableAggressiveVehiclesFromTraffic() override;
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
};
