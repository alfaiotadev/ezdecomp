#include "kestrel/script/actions/SAction_SetGridlockBoatMap.h"

struct SCtxScope;

struct ScriptVar {
    char pad[0x20];
    void* m_pPtr;
    unsigned short m_Value;
};

struct ScriptContext {
    ScriptVar* GetParamVar(int index, SCtxScope* scope) const;
};

struct GridlockBoatMap {
    char pad[0xF0];
    void* m_pPtr;
    unsigned short m_Value;
};

struct DefaultGridlockRoadMap {
    void* m_pPtr;
    unsigned long long m_Value;
};

__attribute__((visibility("hidden"))) extern DefaultGridlockRoadMap* g_pDefaultGridlockRoadMap;
__attribute__((visibility("hidden"))) extern GridlockBoatMap** g_ppGridlockRoadMap;

const char* SAction_SetGridlockBoatMap::GetName() const {
    return "SetGridlockBoatMap";
}

int SAction_SetGridlockBoatMap::GetHashName() const {
    return m_InputVariant;
}

void SAction_SetGridlockBoatMap::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_SetGridlockBoatMap::Exec(ScriptContext& context) {
    DefaultGridlockRoadMap def = *g_pDefaultGridlockRoadMap;
    ScriptVar* p = context.GetParamVar(0, nullptr);
    if (p != nullptr) {
        def.m_pPtr = p->m_pPtr;
        def.m_Value = p->m_Value | (def.m_Value & 0xFFFFFFFFFFFF0000ULL);
    }
    GridlockBoatMap* mgr = *g_ppGridlockRoadMap;
    mgr->m_pPtr = def.m_pPtr;
    mgr->m_Value = static_cast<unsigned short>(def.m_Value);
    return ACTION_FINISHED;
}
