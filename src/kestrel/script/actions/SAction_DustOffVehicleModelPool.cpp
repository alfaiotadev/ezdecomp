#include "kestrel/script/actions/SAction_DustOffVehicleModelPool.h"

struct LevelContainer;

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual LevelContainer* GetLevelContainer() = 0;
};

struct VehicleModelPool {
    void DustOff();
};

class cPopulationManager {
public:
    static cPopulationManager* GetOnly(const LevelContainer* pLevelContainer);
    char pad[9112];
    VehicleModelPool* mpVehicleModelPool;
};

const char* SAction_DustOffVehicleModelPool::GetName() const {
    return "DustOffVehicleModelPool";
}
void SAction_DustOffVehicleModelPool::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_DustOffVehicleModelPool::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_DustOffVehicleModelPool::Exec(ScriptContext& context) {
    cPopulationManager* manager = cPopulationManager::GetOnly(context.GetLevelContainer());
    if (manager != nullptr) {
        VehicleModelPool* pool = manager->mpVehicleModelPool;
        if (pool != nullptr) {
            pool->DustOff();
        }
    }
    return ACTION_FINISHED;
}
