#include "kestrel/script/actions/SAction_Timer2Text.h"

#include <cstdio>

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

struct SVarText;

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    TimerVar* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_Timer2Text::GetName() const {
    return "Text";
}
void SAction_Timer2Text::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TIMER);
}
void SAction_Timer2Text::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}

ActionState SAction_Timer2Text::Exec(ScriptContext& context) {
    TimerVar* timer = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    char buf[16];
    sprintf(buf, "%f.2", timer->m_controller->m_maxTime - timer->m_currentTime);
    context.SetReturn<SVarText, const char*>(0, buf);
    return ACTION_FINISHED;
}
