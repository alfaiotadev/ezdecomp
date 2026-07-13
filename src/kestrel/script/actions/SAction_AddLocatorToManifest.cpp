#include "kestrel/script/actions/SAction_AddLocatorToManifest.h"

const char* SAction_AddLocatorToManifest::GetName() const {
    return "SAction_AddLocatorToManifest";
}
void SAction_AddLocatorToManifest::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
    params.AddParam(SV_NUMBER);
    params.AddParam(SV_LOCATOR);
}

void SAction_AddLocatorToManifest::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
