#include "kestrel/script/actions/CharacterAction_Flee.h"

const char* CharacterAction_Flee::GetName() const {
    return "Character_Flee";
}

void CharacterAction_Flee::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
