#include "kestrel/script/actions/SAction_EnableSkydiveWind.h"

class SkyDiveAddon {
public:
    static bool m_bEnableWindSound;
};

const char* SAction_EnableSkydiveWind::GetName() const {
    return "EnableSkydiveWind";
}
void SAction_EnableSkydiveWind::GetInputs(SCmdParams& params) const {
    ActionInstanceData::GetInputs(params);
}
void SAction_EnableSkydiveWind::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_EnableSkydiveWind::Exec(ScriptContext& context) {
    SkyDiveAddon::m_bEnableWindSound = 1;
    return ACTION_FINISHED;
}
