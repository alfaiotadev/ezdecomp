#include "kestrel/script/actions/SAction_DestroyLegoProgressBackup.h"

const char* SAction_DestroyLegoProgressBackup::GetName() const {
    return "DestroyLegoProgressBackup";
}
void SAction_DestroyLegoProgressBackup::GetInputs(SCmdParams& params) const {
    ActionInstanceData::GetInputs(params);
}
void SAction_DestroyLegoProgressBackup::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}

class LegoProgressSystem {
public:
    void DestroyLegoProgressBackup();
};

extern LegoProgressSystem* g_pLegoProgressSystem;

ActionState SAction_DestroyLegoProgressBackup::Exec(ScriptContext& context) {
    g_pLegoProgressSystem->DestroyLegoProgressBackup();
    return ACTION_FINISHED;
}
