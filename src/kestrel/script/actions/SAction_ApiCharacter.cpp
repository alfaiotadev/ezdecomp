#include "kestrel/script/actions/SAction_ApiCharacter.h"

struct ApiCharacterScriptVariable;

struct sDynamicVariableData {
    void* m_pCharacter;
    const char* m_pText;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    void* m_pCharacter;
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

const char* SAction_ApiCharacter::GetName() const {
    return "Character";
}
void SAction_ApiCharacter::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_TEXT);
    params.AddParam(SV_WORLD_LEVEL);
}
void SAction_ApiCharacter::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_CHARACTER);
}

ActionState SAction_ApiCharacter::Exec(ScriptContext& context) {
    void* pCharacter = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_pCharacter;
    const char* pText = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_pText;
    context.SetReturn<ApiCharacterScriptVariable, sDynamicVariableData>(
        0, sDynamicVariableData{pCharacter, pText});
    return ACTION_FINISHED;
}
