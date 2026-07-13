#include "kestrel/script/actions/SAction_PlayActionMusic.h"

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

class LegoCityGame {
public:
    char pad[0x33f8];
    bool m_PlayActionMusic;
};

extern LegoCityGame* g_pLegoCityGame;

const char* SAction_PlayActionMusic::GetName() const {
    return "PlayActionMusic";
}
void SAction_PlayActionMusic::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_PlayActionMusic::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_PlayActionMusic::Exec(ScriptContext& context) {
    g_pLegoCityGame->m_PlayActionMusic
        = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_Value;
    return ACTION_FINISHED;
}
