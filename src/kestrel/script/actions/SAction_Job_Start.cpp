#include "kestrel/script/actions/SAction_Job_Start.h"

struct ScriptVar {
    char pad[0x0c];
    int m_Type;
    char pad2[0x0c];
    int m_Id;
};

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual void Unknown3() = 0;
    char pad[0x48];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class Job {
public:
    void RequestStart();
};

class SVarJob : public ScriptVar {
public:
    char pad3[0x08];
    Job* m_pJob;
    bool m_bStarted;
    Job* GetJobUsingId() const;
};

const char* SAction_Job_Start::GetName() const {
    return "Job_Start";
}
void SAction_Job_Start::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_JOB);
}
void SAction_Job_Start::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_Job_Start::Exec(ScriptContext& context) {
    ScriptVar* pInput = context.m_ppVars[context.m_InputIndex - 1];
    SVarJob* pJobVar = (SVarJob*)context.GetVarABS(pInput->m_Id);
    if (pJobVar != nullptr && pJobVar->m_Type == 0x24) {
        Job* pJob;
        if (pJobVar->m_bStarted) {
            pJob = pJobVar->m_pJob;
        } else {
            pJob = pJobVar->GetJobUsingId();
            pJobVar->m_pJob = pJob;
            pJobVar->m_bStarted = true;
        }
        if (pJob != nullptr) {
            pJob->RequestStart();
        }
    }
    return ACTION_FINISHED;
}
