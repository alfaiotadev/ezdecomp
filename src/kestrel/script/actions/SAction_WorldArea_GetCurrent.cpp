#include "kestrel/script/actions/SAction_WorldArea_GetCurrent.h"

const char* SAction_WorldArea_GetCurrent::GetName() const {
    return "WorldArea_GetCurrent";
}
void SAction_WorldArea_GetCurrent::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_WorldArea_GetCurrent::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_WORLD_AREA);
}

struct AREADATA {
    char pad[0x350];
};
struct WorldAreaScriptVariable;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

static int* volatile g_pCurrentWorldArea __attribute__((aligned(4096)));
static AREADATA** volatile g_ppWorldAreaArray __attribute__((aligned(4096)));

ActionState SAction_WorldArea_GetCurrent::Exec(ScriptContext& context) {
    int index = *g_pCurrentWorldArea;
    AREADATA* area = nullptr;
    if (index >= 0) {
        area = *g_ppWorldAreaArray + index;
    }
    context.SetReturn<WorldAreaScriptVariable, AREADATA*>(0, area);
    return ACTION_FINISHED;
}
