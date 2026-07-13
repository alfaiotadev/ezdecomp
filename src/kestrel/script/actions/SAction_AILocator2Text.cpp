#include "kestrel/script/actions/SAction_AILocator2Text.h"

struct ScriptVariable {
    virtual ~ScriptVariable();
    virtual float AsFloat() const;
    virtual int AsInt() const;
    virtual bool AsBool() const;
    virtual const char* AsText() const;
};

struct ScriptContext {
    ScriptVariable* GetVar(int);
    void ReturnText(int, const char*);
};

const char* SAction_AILocator2Text::GetName() const {
    return "Text";
}
void SAction_AILocator2Text::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_LOCATOR);
}

void SAction_AILocator2Text::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}

ActionState SAction_AILocator2Text::Exec(ScriptContext& context) {
    context.ReturnText(0, context.GetVar(0)->AsText());
    return ACTION_FINISHED;
}
