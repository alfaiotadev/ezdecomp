#include "kestrel/script/actions/SAction_AtkMngr_Suspend.h"

const char* SAction_AtkMngr_Suspend::GetName() const {
    return "Suspend";
}

void SAction_AtkMngr_Suspend::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
