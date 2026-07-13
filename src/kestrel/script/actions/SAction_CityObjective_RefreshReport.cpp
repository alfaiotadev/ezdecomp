#include "kestrel/script/actions/SAction_CityObjective_RefreshReport.h"

const char* SAction_CityObjective_RefreshReport::GetName() const {
    return "CityObjective_RefreshReport";
}
void SAction_CityObjective_RefreshReport::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_CityObjective_RefreshReport::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

class LegoCityGame {
public:
    void RefreshCityReport();
};

extern LegoCityGame* g_pLegoCityGame;

ActionState SAction_CityObjective_RefreshReport::Exec(ScriptContext& context) {
    g_pLegoCityGame->RefreshCityReport();
    return ACTION_FINISHED;
}
