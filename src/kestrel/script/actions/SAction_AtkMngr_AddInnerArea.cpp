#include "kestrel/script/actions/SAction_AtkMngr_AddInnerArea.h"

const char* SAction_AtkMngr_AddInnerArea::GetName() const {
    return "AddInnerArea";
}

void SAction_AtkMngr_AddInnerArea::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
