#include "kestrel/script/actions/CharacterAction_SetAIOverride.h"

ActionState CharacterAction_SetAIOverride::Exec(ScriptContext& context) {
    return ExecInternal(context, true);
}
