#include "kestrel/script/actions/SAction_GetGoldBrickTotal.h"

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

const char* SAction_GetGoldBrickTotal::GetName() const {
    return "GetGoldBrickTotal";
}
void SAction_GetGoldBrickTotal::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_GetGoldBrickTotal::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_GetGoldBrickTotal::Exec(ScriptContext& context) {
    context.SetReturn<SVarFloat, float>(
        0, static_cast<float>(*g_pLegoCityGame->GetGlobalCollectableStatistic()));
    return ACTION_FINISHED;
}
