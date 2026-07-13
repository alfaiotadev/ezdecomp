#include "kestrel/script/actions/SAction_TutorialSetNoFighting.h"

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

class cAttackManager {
public:
    static bool sm_tutorialNoAttackMode;
};

const char* SAction_TutorialSetNoFighting::GetName() const {
    return "TutorialSetNoFighting";
}
void SAction_TutorialSetNoFighting::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_TutorialSetNoFighting::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_TutorialSetNoFighting::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    cAttackManager::sm_tutorialNoAttackMode = context.GetVarABS(p->m_Id)->m_Value;
    return ACTION_FINISHED;
}
