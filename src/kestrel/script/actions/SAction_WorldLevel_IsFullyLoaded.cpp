#include "kestrel/script/actions/SAction_WorldLevel_IsFullyLoaded.h"

struct SVarBool;

struct __attribute__((packed)) StreamingLevelLOD {
    char pad[0x2d2];
    unsigned int m_Flags : 24;
};

class StreamingLevel {
public:
    StreamingLevelLOD* GetActiveLOD();
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    StreamingLevel* m_pLevel;
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

const char* SAction_WorldLevel_IsFullyLoaded::GetName() const {
    return "WorldLevel_IsFullyLoaded";
}
void SAction_WorldLevel_IsFullyLoaded::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_WORLD_LEVEL);
}
void SAction_WorldLevel_IsFullyLoaded::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_WorldLevel_IsFullyLoaded::Exec(ScriptContext& context) {
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    StreamingLevel* pLevel = context.GetVarABS(input->m_Id)->m_pLevel;
    bool loaded = false;
    if (pLevel != nullptr) {
        StreamingLevelLOD* pLOD = pLevel->GetActiveLOD();
        if (pLOD != nullptr) {
            unsigned int flags = pLOD->m_Flags;
            if (flags & 0x4000) {
                goto end;
            }
            loaded = (flags & 0x8000) == 0;
        }
    }
end:
    context.SetReturn<SVarBool, bool>(0, loaded);
    return ACTION_FINISHED;
}
