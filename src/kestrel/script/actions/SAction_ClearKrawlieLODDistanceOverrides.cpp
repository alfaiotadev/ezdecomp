#include "kestrel/script/actions/SAction_ClearKrawlieLODDistanceOverrides.h"

struct LevelContainer;

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual LevelContainer* GetLevelContainer() = 0;
};

struct MechKrawlieScriptSupport {
    static void ClearLodDistanceOverrides(LevelContainer* pLevelContainer);
};

const char* SAction_ClearKrawlieLODDistanceOverrides::GetName() const {
    return "ClearKrawlieLODDistanceOverrides";
}
void SAction_ClearKrawlieLODDistanceOverrides::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_ClearKrawlieLODDistanceOverrides::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_ClearKrawlieLODDistanceOverrides::Exec(ScriptContext& context) {
    MechKrawlieScriptSupport::ClearLodDistanceOverrides(context.GetLevelContainer());
    return ACTION_FINISHED;
}
