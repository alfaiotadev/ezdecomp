#include "kestrel/script/actions/SAction_ApplyLegoProgressBackup.h"

struct LevelContainer;

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual LevelContainer* GetLevelContainer() = 0;
};

class LegoProgressSystem {
public:
    void ApplyLegoProgressBackUp(LevelContainer& levelContainer);
};

extern LegoProgressSystem* g_pLegoProgressSystem;

const char* SAction_ApplyLegoProgressBackup::GetName() const {
    return "ApplyLegoProgressBackup";
}
void SAction_ApplyLegoProgressBackup::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_ApplyLegoProgressBackup::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_ApplyLegoProgressBackup::Exec(ScriptContext& context) {
    if (context.GetLevelContainer() != nullptr) {
        g_pLegoProgressSystem->ApplyLegoProgressBackUp(*context.GetLevelContainer());
    }
    return ACTION_FINISHED;
}
