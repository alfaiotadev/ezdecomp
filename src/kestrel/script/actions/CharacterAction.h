#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

class CharacterAction : public ActionInstanceData {
public:
    ActionState ExecInternal(ScriptContext& context, bool);
};
