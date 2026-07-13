#include "kestrel/script/actions/SAction_Job_JobToText.h"

const char* SAction_Job_JobToText::GetName() const {
    return "Text";
}
void SAction_Job_JobToText::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_JOB);
}
void SAction_Job_JobToText::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}

class ScriptVariable {
public:
    virtual ~ScriptVariable();
    virtual float AsFloat() const;
    virtual int AsInt() const;
    virtual bool AsBool() const;
    virtual const char* AsText() const;
};

struct SVarText;
struct SCtxScope;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
    ScriptVariable* GetParamVar(int, SCtxScope*) const;
};

ActionState SAction_Job_JobToText::Exec(ScriptContext& context) {
    ScriptVariable* pVar = context.GetParamVar(0, nullptr);
    context.SetReturn<SVarText, const char*>(0, pVar->AsText());
    return ACTION_FINISHED;
}
