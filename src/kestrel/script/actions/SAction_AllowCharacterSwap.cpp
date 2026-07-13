#include "kestrel/script/actions/SAction_AllowCharacterSwap.h"

const char* SAction_AllowCharacterSwap::GetName() const {
    return "AllowCharacterSwap";
}

void SAction_AllowCharacterSwap::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
