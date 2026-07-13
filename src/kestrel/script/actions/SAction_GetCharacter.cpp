#include "kestrel/script/actions/SAction_GetCharacter.h"

struct ApiCharacterScriptVariable;
struct ApiCharacter;

struct LegacyScriptContext {
    ApiCharacter* GetApiCharacter() const;
};

struct ScriptContext : LegacyScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_GetCharacter::GetName() const {
    return "GetCharacter";
}
void SAction_GetCharacter::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_GetCharacter::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CHARACTER, "This ApiCharacter");
}
ActionState SAction_GetCharacter::Exec(ScriptContext& context) {
    context.SetReturn<ApiCharacterScriptVariable, ApiCharacter*>(0, context.GetApiCharacter());
    return ACTION_FINISHED;
}
