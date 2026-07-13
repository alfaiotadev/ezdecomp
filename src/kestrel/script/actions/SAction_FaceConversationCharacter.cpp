#include "kestrel/script/actions/SAction_FaceConversationCharacter.h"

const char* SAction_FaceConversationCharacter::GetName() const {
    return "FaceConversationCharacter";
}
void SAction_FaceConversationCharacter::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CHARACTER);
    params.AddParam(SV_TEXT);
    params.AddParam(SV_NUMBER);
}
void SAction_FaceConversationCharacter::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
