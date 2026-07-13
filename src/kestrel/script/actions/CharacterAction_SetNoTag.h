#pragma once

struct ApiCharacter;
struct ScriptContext;

class CharacterAction_SetNoTag {
public:
    static bool CharacterExec(ApiCharacter* pCharacter, ScriptContext& context);
};
