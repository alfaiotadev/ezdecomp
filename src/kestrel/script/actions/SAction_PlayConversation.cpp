#include "kestrel/script/actions/SAction_PlayConversation.h"

const char* SAction_PlayConversation::GetName() const {
    return "PlayConversation";
}

void SAction_PlayConversation::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
