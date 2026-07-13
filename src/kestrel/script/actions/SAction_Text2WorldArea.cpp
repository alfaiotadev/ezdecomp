#include "kestrel/script/actions/SAction_Text2WorldArea.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
    char pad2[0x7];
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

struct AREADATA {
    char pad[0x350];
};

struct WorldAreaScriptVariable;

AREADATA* Area_FindByName(const char*, int*);

const char* SAction_Text2WorldArea::GetName() const {
    return "WorldArea";
}
void SAction_Text2WorldArea::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_Text2WorldArea::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_WORLD_AREA);
}

ActionState SAction_Text2WorldArea::Exec(ScriptContext& context) {
    const char* name = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    int index = -1;
    AREADATA* area = Area_FindByName(name, &index);
    context.SetReturn<WorldAreaScriptVariable, AREADATA*>(0, area);
    return ACTION_FINISHED;
}
