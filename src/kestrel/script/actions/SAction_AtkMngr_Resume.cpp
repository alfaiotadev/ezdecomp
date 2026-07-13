#include "kestrel/script/actions/SAction_AtkMngr_Resume.h"

const char* SAction_AtkMngr_Resume::GetName() const {
    return "Resume";
}

void SAction_AtkMngr_Resume::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
