#pragma once

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_ResetToOrigin {
public:
    static bool CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
};
