#include "kestrel/script/actions/SAction_AtkMngr_AddAttacker.h"

const char* SAction_AtkMngr_AddAttacker::GetName() const {
    return "AddAttacker";
}

void SAction_AtkMngr_AddAttacker::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
