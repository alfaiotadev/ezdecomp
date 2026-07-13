#include "kestrel/script/actions/SAction_AtkMngr_FinishAreaDefinition.h"

const char* SAction_AtkMngr_FinishAreaDefinition::GetName() const {
    return "FinishAreaDefinition";
}
void SAction_AtkMngr_FinishAreaDefinition::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
