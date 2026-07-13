#include "kestrel/script/actions/CharacterAction_GetModelName.h"

struct ApiCharacterData {
    char pad[48];
    const char* text;
};

struct ApiCharacter {
    char pad[1552];
    ApiCharacterData* data;
};

struct ScriptContext {
    void ReturnText(int, const char*);
};

ActionState CharacterAction_GetModelName::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    context.ReturnText(0, pCharacter->data->text);
    return ACTION_FINISHED;
}
