#include "kestrel/script/actions/SAction_AtkMngr_AddOuterArea.h"

const char* SAction_AtkMngr_AddOuterArea::GetName() const {
    return "AddOuterArea";
}

void SAction_AtkMngr_AddOuterArea::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
