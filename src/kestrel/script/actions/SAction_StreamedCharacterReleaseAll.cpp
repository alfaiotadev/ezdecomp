#include "kestrel/script/actions/SAction_StreamedCharacterReleaseAll.h"

struct ScriptContext {
    const char* GetScriptName() const;
};

struct StreamedCharacterManager {
    char pad[216];
    void* m_pActive;
    void ReleaseStrongRefs(unsigned long hash);
};

extern StreamedCharacterManager*
    g_pStreamedCharacterManager __asm__("_ZN12SystemMixinsI24StreamedCharacterManagerE11m_singletonE");

extern unsigned int NuStrHashFNV1(const char* str, unsigned int seed);

const char* SAction_StreamedCharacterReleaseAll::GetName() const {
    return "StreamedCharacterReleaseAll";
}
void SAction_StreamedCharacterReleaseAll::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_StreamedCharacterReleaseAll::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_StreamedCharacterReleaseAll::Exec(ScriptContext& context) {
    StreamedCharacterManager* const& mgr = g_pStreamedCharacterManager;
    if (mgr != nullptr && mgr->m_pActive != nullptr) {
        const char* scriptName = context.GetScriptName();
        unsigned int hash = scriptName ? NuStrHashFNV1(scriptName, 0x811c9dc5) : 0;
        mgr->ReleaseStrongRefs(hash);
    }
    return ACTION_FINISHED;
}
