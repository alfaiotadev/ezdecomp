#include "kestrel/script/actions/SAction_UI_PDA_ShowBusyIcon.h"

const char* SAction_UI_PDA_ShowBusyIcon::GetName() const {
    return "UI_PDA_ShowBusyIcon";
}

void SAction_UI_PDA_ShowBusyIcon::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
