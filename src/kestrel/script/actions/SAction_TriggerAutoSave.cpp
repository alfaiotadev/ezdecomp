#include "kestrel/script/actions/SAction_TriggerAutoSave.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarBool {
    char pad[0x20];
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

struct SafeGuard {
    void TriggerAutoSave();
};

class LegoCityGame {
public:
    static SafeGuard* GetSafeGuard();
};

extern int _ZN16LegoCitySaveGame27s_checkpointSavePromptStateE __asm__(
    "_ZN16LegoCitySaveGame27s_checkpointSavePromptStateE");

const char* SAction_TriggerAutoSave::GetName() const {
    return "TriggerAutoSave";
}
void SAction_TriggerAutoSave::GetInputs(SCmdParams& params) const {
    if (!*reinterpret_cast<const uint8_t*>(&m_InputVariant)) {
        ActionInstanceData::GetInputs(params);
        return;
    }
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_TriggerAutoSave::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_TriggerAutoSave::Exec(ScriptContext& context) {
    LegoCityGame::GetSafeGuard()->TriggerAutoSave();
    if (*reinterpret_cast<const uint8_t*>(&m_InputVariant)) {
        SVarBool* p = (SVarBool*)context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
        if (p->m_Value) {
            _ZN16LegoCitySaveGame27s_checkpointSavePromptStateE = 1;
        }
    }
    return ACTION_FINISHED;
}
