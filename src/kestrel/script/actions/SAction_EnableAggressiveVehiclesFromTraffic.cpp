#include "kestrel/script/actions/SAction_EnableAggressiveVehiclesFromTraffic.h"

SAction_EnableAggressiveVehiclesFromTraffic::~SAction_EnableAggressiveVehiclesFromTraffic() = default;

const char* SAction_EnableAggressiveVehiclesFromTraffic::GetName() const {
    return "EnableAggressiveVehiclesFromTraffic";
}

void SAction_EnableAggressiveVehiclesFromTraffic::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
