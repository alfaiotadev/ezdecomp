#include "kestrel/script/actions/SAction_IsGameCompleteCheatActive.h"

struct SVarBool;
struct CHEAT_s {
    char pad[0x20];
};

class LegoCityGame {
public:
    char pad[0xa50];
    CHEAT_s m_GameCompleteCheat;
};

__attribute__((visibility("hidden"))) LegoCityGame* g_pLegoCityGame;
int Cheat_IsOn(CHEAT_s*);

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_IsGameCompleteCheatActive::GetName() const {
    return "IsGameCompleteCheatActive";
}
void SAction_IsGameCompleteCheatActive::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_IsGameCompleteCheatActive::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_IsGameCompleteCheatActive::Exec(ScriptContext& context) {
    context.SetReturn<SVarBool, bool>(0, Cheat_IsOn(&g_pLegoCityGame->m_GameCompleteCheat) != 0);
    return ACTION_FINISHED;
}
