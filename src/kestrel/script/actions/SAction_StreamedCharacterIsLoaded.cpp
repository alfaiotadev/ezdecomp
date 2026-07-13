#include "kestrel/script/actions/SAction_StreamedCharacterIsLoaded.h"

const char* SAction_StreamedCharacterIsLoaded::GetName() const {
    return "StreamedCharacterIsLoaded";
}
void SAction_StreamedCharacterIsLoaded::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_StreamedCharacterIsLoaded::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

struct SVarBool;

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    int pad2;
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

class LegoCharacters {
public:
    int GetCIDFromName(const char*) const;
};

struct StreamedCharacterManager {
    static bool IsLoaded(int);
};

extern LegoCharacters* g_pLegoCharacters __asm__("_ZN12SystemMixinsI14LegoCharactersE11m_singletonE");

ActionState SAction_StreamedCharacterIsLoaded::Exec(ScriptContext& context) {
    unsigned char idx = context.m_InputIndex;
    ScriptVar* v = context.m_ppVars[idx - 1];
    int id = v->m_Id;
    ScriptVar* var = context.GetVarABS(id);
    const char* name = var->m_pText;
    int cid = g_pLegoCharacters->GetCIDFromName(name);
    bool loaded = StreamedCharacterManager::IsLoaded(cid);
    context.SetReturn<SVarBool, bool>(0, loaded);
    return ACTION_FINISHED;
}
