#include "kestrel/script/actions/SAction_DestroyKrawliesInGroup.h"

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

struct MechKrawlieGroup {
    void RemoveAllKrawlies();
};

struct MechKrawlieScriptSupport {
    static MechKrawlieGroup* FindKrawlieGroup(LevelContainer* pLevelContainer, const char* pName);
};

const char* SAction_DestroyKrawliesInGroup::GetName() const {
    return "DestroyKrawliesInGroup";
}
void SAction_DestroyKrawliesInGroup::GetInputs(SCmdParams& params) const {
    params.AddParam(SV_TEXT);
}
void SAction_DestroyKrawliesInGroup::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}

ActionState SAction_DestroyKrawliesInGroup::Exec(ScriptContext& context) {
    LevelContainer* pLevelContainer = context.GetLevelContainer();
    ScriptVar* pVar = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    MechKrawlieGroup* pGroup = MechKrawlieScriptSupport::FindKrawlieGroup(pLevelContainer, pVar->m_pText);
    if (pGroup != nullptr) {
        pGroup->RemoveAllKrawlies();
        return ACTION_FINISHED;
    }
    return ACTION_UNKNOWN_7;
}
