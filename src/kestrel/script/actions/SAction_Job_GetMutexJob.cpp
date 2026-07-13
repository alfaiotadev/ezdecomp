#include "kestrel/script/actions/SAction_Job_GetMutexJob.h"

class Job {
public:
    int GetId() const;
};

struct ScriptContext;

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

class SVarJob {
public:
    static void ReturnToContext(Job* pJob, ScriptContext& context, int index);
};

const char* SAction_Job_GetMutexJob::GetName() const {
    return "Job_GetMutexJob";
}
void SAction_Job_GetMutexJob::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_Job_GetMutexJob::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_JOB);
}

ActionState SAction_Job_GetMutexJob::Exec(ScriptContext& context) {
    JobManager* pManager = JobManager::GetFromContext(context);
    Job* pJob = nullptr;
    if (pManager != nullptr) {
        pJob = pManager->GetMutexManager()->m_pMutexJob;
    }
    SVarJob::ReturnToContext(pJob, context, 0);
    return ACTION_FINISHED;
}
