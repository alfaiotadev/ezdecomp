#include "kestrel/script/actions/SAction_SetObjectiveMarker.h"

const char* SAction_SetObjectiveMarker::GetName() const {
    return "SetObjectiveMarker";
}
void SAction_SetObjectiveMarker::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
