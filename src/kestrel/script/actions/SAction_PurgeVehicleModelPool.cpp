#include "kestrel/script/actions/SAction_PurgeVehicleModelPool.h"

struct LevelContainer;

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual LevelContainer* GetLevelContainer() = 0;
};

struct VehicleModelPool {
    void PurgeAll();
};

class cPopulationManager {
public:
    static cPopulationManager* GetOnly(const LevelContainer* pLevelContainer);
    char pad[9112];
    VehicleModelPool* mpVehicleModelPool;
};

const char* SAction_PurgeVehicleModelPool::GetName() const {
    return "PurgeVehicleModelPool";
}
void SAction_PurgeVehicleModelPool::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_PurgeVehicleModelPool::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_PurgeVehicleModelPool::Exec(ScriptContext& context) {
    cPopulationManager* manager = cPopulationManager::GetOnly(context.GetLevelContainer());
    if (manager != nullptr) {
        VehicleModelPool* pool = manager->mpVehicleModelPool;
        if (pool != nullptr) {
            pool->PurgeAll();
        }
    }
    return ACTION_FINISHED;
}
