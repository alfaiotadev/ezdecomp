#include "kestrel/script/actions/SAction_GetPlayerBricks.h"

struct SVarFloat;

class LegoCityGame {
public:
    int GetPickupBrickCount();
};

extern LegoCityGame* g_pLegoCityGame;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_GetPlayerBricks::GetName() const {
    return "GetPlayerBricks";
}
void SAction_GetPlayerBricks::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_GetPlayerBricks::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_GetPlayerBricks::Exec(ScriptContext& context) {
    LegoCityGame* game = g_pLegoCityGame;
    int count = game->GetPickupBrickCount();
    context.SetReturn<SVarFloat, float>(0, static_cast<float>(count));
    return ACTION_FINISHED;
}
