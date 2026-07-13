#include "kestrel/script/actions/SAction_GetClassUnlocked.h"

struct SVarBool;

struct HashedKey {
    unsigned int m_Hash;
};

enum eCharClass : unsigned int;

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

class LegoCityCharacters {
public:
    static eCharClass GetClassFromHash(const HashedKey& key);
    static bool IsClassUnlocked(const eCharClass& cls);
};

unsigned int NuStrHashUpperCaseFNV1(const char* str, unsigned int hash);

const char* SAction_GetClassUnlocked::GetName() const {
    return "GetClassUnlocked";
}
void SAction_GetClassUnlocked::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
}
void SAction_GetClassUnlocked::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_GetClassUnlocked::Exec(ScriptContext& context) {
    const char* text = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    unsigned int hash = 0;
    if (text != nullptr) {
        hash = NuStrHashUpperCaseFNV1(text, 0x811c9dc5);
    }
    HashedKey key = {hash};
    eCharClass cls = LegoCityCharacters::GetClassFromHash(key);
    bool unlocked = LegoCityCharacters::IsClassUnlocked(cls);
    context.SetReturn<SVarBool, bool>(0, unlocked);
    return ACTION_FINISHED;
}
