#include "kestrel/script/actions/SAction_ResetTimer.h"

struct TimerController {
    char pad[0x74];
    float m_maxTime;
};

struct TimerVar {
    char pad[0x20];
    float m_currentTime;
    char pad2[0x4];
    TimerController* m_controller;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    TimerVar* GetVarABS(int id) const;
};

const char* SAction_ResetTimer::GetName() const {
    return "Timer_Reset";
}
void SAction_ResetTimer::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TIMER);
}
void SAction_ResetTimer::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_ResetTimer::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    TimerVar* timer = context.GetVarABS(p->m_Id);
    timer->m_currentTime = 0.0f + timer->m_controller->m_maxTime;
    return ACTION_FINISHED;
}
