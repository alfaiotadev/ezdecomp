#include "kestrel/script/actions/CharacterAction_IsOn.h"

const char* CharacterAction_IsOn::GetName() const {
    return "IsOn";
}

ActionState CharacterAction_IsOn::Exec(ScriptContext& context) {
    return ExecInternal(context, true);
}
