#include "kestrel/script/actions/SAction_CreateLegoProgressBackup.h"

struct LevelContainer;

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual LevelContainer* GetLevelContainer() = 0;
};

class LegoProgressSystem {
public:
    void CreateLegoProgressBackUp(LevelContainer& levelContainer);
};

extern LegoProgressSystem* g_pLegoProgressSystem;

const char* SAction_CreateLegoProgressBackup::GetName() const {
    return "CreateLegoProgressBackup";
}
void SAction_CreateLegoProgressBackup::GetInputs(SCmdParams& params) const {
    ActionInstanceData::GetInputs(params);
}
void SAction_CreateLegoProgressBackup::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}

ActionState SAction_CreateLegoProgressBackup::Exec(ScriptContext& context) {
    if (context.GetLevelContainer() != nullptr) {
        g_pLegoProgressSystem->CreateLegoProgressBackUp(*context.GetLevelContainer());
    }
    return ACTION_FINISHED;
}
