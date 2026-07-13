#include "kestrel/script/actions/SAction_WorldArea_IsCurrentWorldArea.h"

struct AREADATA {
    char pad[0x184];
    unsigned char m_index;
    char pad2[0x350 - 0x184 - 1];
};

struct SVarBool;
struct WorldAreaScriptVariable;

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    AREADATA* m_pArea;
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

static int* volatile g_pCurrentWorldArea __attribute__((aligned(4096)));

const char* SAction_WorldArea_IsCurrentWorldArea::GetName() const {
    return "WorldArea_IsCurrentWorldArea";
}
void SAction_WorldArea_IsCurrentWorldArea::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_WORLD_AREA);
}
void SAction_WorldArea_IsCurrentWorldArea::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_WorldArea_IsCurrentWorldArea::Exec(ScriptContext& context) {
    AREADATA* pArea = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pArea;
    bool isCurrent = pArea && pArea->m_index == *g_pCurrentWorldArea;
    context.SetReturn<SVarBool, bool>(0, isCurrent);
    return ACTION_FINISHED;
}
