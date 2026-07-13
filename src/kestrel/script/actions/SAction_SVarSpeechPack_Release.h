#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_SVarSpeechPack_Release : public ActionInstanceData {
public:
    const char* GetName() const override;
    void GetOutputs(SCmdParams& params) const override;
};
