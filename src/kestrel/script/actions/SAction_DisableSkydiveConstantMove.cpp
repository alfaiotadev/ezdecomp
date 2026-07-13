#include "kestrel/script/actions/SAction_DisableSkydiveConstantMove.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarCharacter {
    char pad[0x48];
    void* m_pCharacter;
};

struct ApiCharacter {
    char pad[0xb5];
    unsigned char m_Flags;
};

struct MechCharacter {};

struct ScriptContext {
    char pad[0x39];
    unsigned char m_VarCount;
    char pad2[0x50 - 0x3a];
    ScriptVar** m_ppVars;
    char pad3;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class SkyDiveAddon {
public:
    static void DisableConstantMove(MechCharacter* pMech);
};

const char* SAction_DisableSkydiveConstantMove::GetName() const {
    return "DisableSkydiveConstantMove";
}

void SAction_DisableSkydiveConstantMove::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}

ActionState SAction_DisableSkydiveConstantMove::Exec(ScriptContext& context) {
    if (*reinterpret_cast<const uint8_t*>(&m_InputVariant) == 0) {
        SkyDiveAddon::DisableConstantMove(nullptr);
        return ACTION_FINISHED;
    }
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    unsigned char count = context.m_VarCount;
    int id = input->m_Id;
    if (count <= id) {
        SkyDiveAddon::DisableConstantMove(nullptr);
        return ACTION_FINISHED;
    }
    SVarCharacter* p = (SVarCharacter*)context.GetVarABS(id);
    if (p->m_pCharacter == nullptr) {
        SkyDiveAddon::DisableConstantMove(nullptr);
        return ACTION_FINISHED;
    }
    unsigned char flags = ((ApiCharacter*)p->m_pCharacter)->m_Flags;
    if ((flags & 0x10) != 0) {
        SkyDiveAddon::DisableConstantMove((MechCharacter*)((char*)p->m_pCharacter - 0x10));
    } else {
        SkyDiveAddon::DisableConstantMove(nullptr);
    }
    return ACTION_FINISHED;
}
