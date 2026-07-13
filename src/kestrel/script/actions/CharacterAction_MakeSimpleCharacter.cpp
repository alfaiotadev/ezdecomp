#include "kestrel/script/actions/CharacterAction_MakeSimpleCharacter.h"

const char* CharacterAction_MakeSimpleCharacter::GetName() const {
    return "MakeSimpleCharacter";
}

bool CharacterAction_MakeSimpleCharacter::CharacterExec(ApiCharacter*, ScriptContext&) {
    return true;
}

void CharacterAction_MakeSimpleCharacter::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
