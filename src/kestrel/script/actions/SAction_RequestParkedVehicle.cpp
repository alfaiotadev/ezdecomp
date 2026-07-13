#include "kestrel/script/actions/SAction_RequestParkedVehicle.h"

const char* SAction_RequestParkedVehicle::GetName() const {
    return "RequestParkedVehicle";
}

void SAction_RequestParkedVehicle::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
