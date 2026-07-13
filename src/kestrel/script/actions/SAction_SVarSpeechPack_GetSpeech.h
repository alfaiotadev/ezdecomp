#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_SVarSpeechPack_GetSpeech : public ActionInstanceData {
public:
    const char* GetName() const override;
};
