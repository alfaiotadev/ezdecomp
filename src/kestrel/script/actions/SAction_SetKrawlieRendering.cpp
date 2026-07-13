#include "kestrel/script/actions/SAction_SetKrawlieRendering.h"

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
    static void SetManagerRendering(LevelContainer* pLevelContainer, bool enabled);
};

const char* SAction_SetKrawlieRendering::GetName() const {
    return "SetKrawlieRendering";
}
void SAction_SetKrawlieRendering::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_SetKrawlieRendering::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetKrawlieRendering::Exec(ScriptContext& context) {
    LevelContainer* pLevelContainer = context.GetLevelContainer();
    ScriptVar* pVar = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    MechKrawlieScriptSupport::SetManagerRendering(pLevelContainer, pVar->m_Value);
    return ACTION_FINISHED;
}
