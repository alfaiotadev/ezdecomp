#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_SVarSpeech_IsPlaying : public ActionInstanceData {
public:
    const char* GetName() const override;
};
