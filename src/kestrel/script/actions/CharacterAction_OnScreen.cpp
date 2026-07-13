#include "kestrel/script/actions/CharacterAction_OnScreen.h"

const char* CharacterAction_OnScreen::GetName() const {
    return "OnScreen";
}

struct SVarBool;

struct ApiCharacter {
    char pad[531];
    unsigned char onScreen;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState CharacterAction_OnScreen::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    bool onScreen = pCharacter != nullptr && pCharacter->onScreen != 0;
    context.SetReturn<SVarBool, bool>(0, onScreen);
    return ACTION_FINISHED;
}
