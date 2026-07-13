#include "kestrel/script/actions/SAction_KillSpawnedTraffic.h"

struct LevelContainer;

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual LevelContainer* GetLevelContainer() = 0;
};

class cPopulationManager {
public:
    static cPopulationManager* GetOnly(const LevelContainer* pLevelContainer);
    void DestroyRandomPopulation();
};

const char* SAction_KillSpawnedTraffic::GetName() const {
    return "KillSpawnedTraffic";
}
void SAction_KillSpawnedTraffic::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_KillSpawnedTraffic::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_KillSpawnedTraffic::Exec(ScriptContext& context) {
    cPopulationManager::GetOnly(context.GetLevelContainer())->DestroyRandomPopulation();
    return ACTION_FINISHED;
}
