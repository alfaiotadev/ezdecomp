#include "kestrel/script/actions/SAction_ShowTaggingIcon.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class LegoCityTagging {
public:
    static bool s_CanShowTagButton;
};

const char* SAction_ShowTaggingIcon::GetName() const {
    return "ShowTaggingIcon";
}
void SAction_ShowTaggingIcon::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_ShowTaggingIcon::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_ShowTaggingIcon::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    LegoCityTagging::s_CanShowTagButton = context.GetVarABS(p->m_Id)->m_Value;
    return ACTION_FINISHED;
}
