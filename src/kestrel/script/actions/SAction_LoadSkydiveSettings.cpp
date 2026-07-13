#include "kestrel/script/actions/SAction_LoadSkydiveSettings.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int pad2;
    const char* m_String;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class SkyDiveAddon {
public:
    static void SelectSkydiveSettings(const char* settings);
};

const char* SAction_LoadSkydiveSettings::GetName() const {
    return "LoadSkydiveSettings";
}
void SAction_LoadSkydiveSettings::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_LoadSkydiveSettings::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_LoadSkydiveSettings::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    SkyDiveAddon::SelectSkydiveSettings(context.GetVarABS(p->m_Id)->m_String);
    return ACTION_FINISHED;
}
