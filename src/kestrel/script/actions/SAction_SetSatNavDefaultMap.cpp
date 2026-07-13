#include "kestrel/script/actions/SAction_SetSatNavDefaultMap.h"

struct SCtxScope;

struct ScriptVar {
    char pad[0x20];
    unsigned short m_Value;
};

struct ScriptContext {
    ScriptVar* GetParamVar(int index, SCtxScope* scope) const;
};

struct SatNavManager {
    char pad[0x100];
    unsigned short m_DefaultMap;
};

__attribute__((visibility("hidden"))) SatNavManager** g_ppSatNavManager;

const char* SAction_SetSatNavDefaultMap::GetName() const {
    return "SetSatNavDefaultMap";
}
void SAction_SetSatNavDefaultMap::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NAVI_MAP);
}
void SAction_SetSatNavDefaultMap::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetSatNavDefaultMap::Exec(ScriptContext& context) {
    ScriptVar* p = context.GetParamVar(0, nullptr);
    unsigned short value = (p != nullptr) ? p->m_Value : 0xFFFF;
    (*g_ppSatNavManager)->m_DefaultMap = value;
    return ACTION_FINISHED;
}
