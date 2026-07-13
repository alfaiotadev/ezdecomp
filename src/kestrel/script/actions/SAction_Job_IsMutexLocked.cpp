#include "kestrel/script/actions/SAction_Job_IsMutexLocked.h"

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

class Job;

class JobManager {
public:
    class MutexManager;
    MutexManager* GetMutexManager();
    static JobManager* GetFromContext(ScriptContext& context);
};

class JobManager::MutexManager {
    char pad[0x1c8];

public:
    Job* m_pMutexJob;
};

const char* SAction_Job_IsMutexLocked::GetName() const {
    return "Job_IsMutexLocked";
}
void SAction_Job_IsMutexLocked::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_Job_IsMutexLocked::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_Job_IsMutexLocked::Exec(ScriptContext& context) {
    JobManager* pManager = JobManager::GetFromContext(context);
    bool locked = false;
    if (pManager != nullptr) {
        locked = pManager->GetMutexManager()->m_pMutexJob != nullptr;
    }
    context.SetReturn<SVarBool, bool>(0, locked);
    return ACTION_FINISHED;
}
