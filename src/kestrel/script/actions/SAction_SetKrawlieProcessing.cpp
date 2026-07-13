#include "kestrel/script/actions/SAction_SetKrawlieProcessing.h"

struct LevelContainer;

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
    char pad2[0x7];
    const char* m_pText;
};

struct ScriptContext {
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual LevelContainer* GetLevelContainer() = 0;
    char pad[0x48];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct MechKrawlieScriptSupport {
    static void SetManagerProcessing(LevelContainer* pLevelContainer, bool enabled);
};

const char* SAction_SetKrawlieProcessing::GetName() const {
    return "SetKrawlieProcessing";
}
void SAction_SetKrawlieProcessing::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_SetKrawlieProcessing::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetKrawlieProcessing::Exec(ScriptContext& context) {
    LevelContainer* pLevelContainer = context.GetLevelContainer();
    ScriptVar* pVar = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    MechKrawlieScriptSupport::SetManagerProcessing(pLevelContainer, pVar->m_Value);
    return ACTION_FINISHED;
}
