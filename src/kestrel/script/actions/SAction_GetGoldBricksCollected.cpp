#include "kestrel/script/actions/SAction_GetGoldBricksCollected.h"

struct SVarFloat;

class LegoCityGame {
public:
    int* GetGlobalCollectableStatistic();
};

extern LegoCityGame* g_pLegoCityGame;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_GetGoldBricksCollected::GetName() const {
    return "GetGoldBricksCollected";
}
void SAction_GetGoldBricksCollected::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_GetGoldBricksCollected::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_GetGoldBricksCollected::Exec(ScriptContext& context) {
    context.SetReturn<SVarFloat, float>(
        0, static_cast<float>(g_pLegoCityGame->GetGlobalCollectableStatistic()[1]));
    return ACTION_FINISHED;
}
