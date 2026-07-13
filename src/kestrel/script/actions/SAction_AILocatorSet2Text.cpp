#include "kestrel/script/actions/SAction_AILocatorSet2Text.h"

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

const char* SAction_AILocatorSet2Text::GetName() const {
    return "Text";
}
void SAction_AILocatorSet2Text::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_LOCATOR_SET);
}

void SAction_AILocatorSet2Text::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}

ActionState SAction_AILocatorSet2Text::Exec(ScriptContext& context) {
    context.ReturnText(0, context.GetVar(0)->AsText());
    return ACTION_FINISHED;
}
