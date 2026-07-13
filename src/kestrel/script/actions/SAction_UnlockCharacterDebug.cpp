#include "kestrel/script/actions/SAction_UnlockCharacterDebug.h"

const char* SAction_UnlockCharacterDebug::GetName() const {
    return "UnlockCharacterDebug";
}

void SAction_UnlockCharacterDebug::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}

ActionState SAction_UnlockCharacterDebug::Exec(ScriptContext& context) {
    return ActionInstanceData::Exec(context);
}
