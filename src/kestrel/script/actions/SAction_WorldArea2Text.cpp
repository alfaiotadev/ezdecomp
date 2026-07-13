#include "kestrel/script/actions/SAction_WorldArea2Text.h"

const char* SAction_WorldArea2Text::GetName() const {
    return "Text";
}
void SAction_WorldArea2Text::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_WORLD_AREA);
}
void SAction_WorldArea2Text::GetOutputs(SCmdParams& params) const {
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

ActionState SAction_WorldArea2Text::Exec(ScriptContext& context) {
    ScriptVariable* pVar = context.GetParamVar(0, nullptr);
    context.SetReturn<SVarText, const char*>(0, pVar->AsText());
    return ACTION_FINISHED;
}
