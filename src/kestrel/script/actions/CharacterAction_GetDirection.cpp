#include "kestrel/script/actions/CharacterAction_GetDirection.h"

struct SVarFloat;

struct ApiCharacter {
    float GetHeading() const;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState CharacterAction_GetDirection::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    float heading = pCharacter->GetHeading();
    int angle = (int)(heading * 10430.3779296875f) & 0xffff;
    context.SetReturn<SVarFloat, float>(0, static_cast<float>(angle));
    return ACTION_FINISHED;
}
