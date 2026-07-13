#include "kestrel/script/actions/SAction_DisableSkydiveWind.h"

class SkyDiveAddon {
public:
    static bool m_bEnableWindSound;
};

const char* SAction_DisableSkydiveWind::GetName() const {
    return "DisableSkydiveWind";
}
void SAction_DisableSkydiveWind::GetInputs(SCmdParams& params) const {
    ActionInstanceData::GetInputs(params);
}
void SAction_DisableSkydiveWind::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}
ActionState SAction_DisableSkydiveWind::Exec(ScriptContext& context) {
    SkyDiveAddon::m_bEnableWindSound = 0;
    return ACTION_FINISHED;
}
