#include "kestrel/script/actions/SAction_Job_TextToJob.h"

struct SVarJob;

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int pad2;
    const char* m_pText;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

unsigned int NuStrHashUpperCaseFNV1(const char* str, unsigned int hash);

const char* SAction_Job_TextToJob::GetName() const {
    return "Job";
}
void SAction_Job_TextToJob::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_Job_TextToJob::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_JOB);
}

ActionState SAction_Job_TextToJob::Exec(ScriptContext& context) {
    const char* text = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    unsigned int result = 0;
    if (text != nullptr && text[0] != '\0') {
        result = NuStrHashUpperCaseFNV1(
            context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText, 0x811c9dc5);
    }
    context.SetReturn<SVarJob, unsigned int>(0, result);
    return ACTION_FINISHED;
}
