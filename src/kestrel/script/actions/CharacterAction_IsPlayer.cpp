#include "kestrel/script/actions/CharacterAction_IsPlayer.h"

struct ApiCharacter {
    char pad[929];
    bool isPlayer;
};

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState CharacterAction_IsPlayer::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, pCharacter->isPlayer);
    return ACTION_FINISHED;
}
