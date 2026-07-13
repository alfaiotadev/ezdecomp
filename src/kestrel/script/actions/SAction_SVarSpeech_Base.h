#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_SVarSpeech_Base : public ActionInstanceData {
public:
    virtual ActionState DoExec(ScriptContext& context, bool* value) = 0;
    ActionState Exec(ScriptContext& context) override;
};
