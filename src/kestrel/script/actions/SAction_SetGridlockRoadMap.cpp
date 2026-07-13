#include "kestrel/script/actions/SAction_SetGridlockRoadMap.h"

struct SCtxScope;

struct ScriptVar {
    char pad[0x20];
    void* m_pPtr;
    unsigned short m_Value;
};

struct ScriptContext {
    ScriptVar* GetParamVar(int index, SCtxScope* scope) const;
};

struct GridlockRoadMap {
    char pad[0xE0];
    void* m_pPtr;
    unsigned short m_Value;
};

struct DefaultGridlockRoadMap {
    void* m_pPtr;
    unsigned long long m_Value;
};

__attribute__((visibility("hidden"))) DefaultGridlockRoadMap* g_pDefaultGridlockRoadMap;
__attribute__((visibility("hidden"))) GridlockRoadMap** g_ppGridlockRoadMap;

const char* SAction_SetGridlockRoadMap::GetName() const {
    return "SetGridlockRoadMap";
}

void SAction_SetGridlockRoadMap::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

int SAction_SetGridlockRoadMap::GetHashName() const {
    return m_InputVariant;
}

ActionState SAction_SetGridlockRoadMap::Exec(ScriptContext& context) {
    DefaultGridlockRoadMap def = *g_pDefaultGridlockRoadMap;
    ScriptVar* p = context.GetParamVar(0, nullptr);
    if (p != nullptr) {
        def.m_pPtr = p->m_pPtr;
        def.m_Value = p->m_Value | (def.m_Value & 0xFFFFFFFFFFFF0000ULL);
    }
    GridlockRoadMap* mgr = *g_ppGridlockRoadMap;
    mgr->m_pPtr = def.m_pPtr;
    mgr->m_Value = static_cast<unsigned short>(def.m_Value);
    return ACTION_FINISHED;
}
