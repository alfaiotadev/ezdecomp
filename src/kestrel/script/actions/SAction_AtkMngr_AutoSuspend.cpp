#include "kestrel/script/actions/SAction_AtkMngr_AutoSuspend.h"

const char* SAction_AtkMngr_AutoSuspend::GetName() const {
    return "AutoSuspend";
}

void SAction_AtkMngr_AutoSuspend::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
