#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class SAction_SVarSoundListener_Base : public ActionInstanceData {
public:
    virtual ActionState DoExec(ScriptContext& context, const char* text) = 0;
    ActionState Exec(ScriptContext& context) override;
};
