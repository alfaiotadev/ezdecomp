#include "kestrel/script/actions/SAction_ShowObjectiveMarker.h"

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
};

struct ObjectiveTracker {
    struct ObjectiveMarker {
        void Show(bool);
    };
    ObjectiveMarker* GetObjectiveMarker();
};

struct LegoCityGameState {
    char pad[232];
    ObjectiveTracker* objectiveTracker;
};

extern LegoCityGameState* g_pLegoCityGameState;

const char* SAction_ShowObjectiveMarker::GetName() const {
    return "ShowObjectiveMarker";
}
void SAction_ShowObjectiveMarker::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_ShowObjectiveMarker::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_ShowObjectiveMarker::Exec(ScriptContext& context) {
    g_pLegoCityGameState->objectiveTracker->GetObjectiveMarker()->Show(
        context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_Value);
    return ACTION_FINISHED;
}
