#include "kestrel/script/actions/SAction_UI_Map_TransformHintArrow_PlayerSpecific.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct PlayerSpecificSource {
    char pad[0x3a3];
    signed char m_PlayerIndex;
};

struct SVarPlayerSpecific {
    char pad[0x48];
    PlayerSpecificSource* m_pSource;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarPlayerSpecific* GetVarABS(int id) const;
};

extern void DoTransform(ScriptContext&, int, int);

const char* SAction_UI_Map_TransformHintArrow_PlayerSpecific::GetName() const {
    return "UI_Map_TransformHintArrow_PlayerSpecific";
}
void SAction_UI_Map_TransformHintArrow_PlayerSpecific::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_Map_TransformHintArrow_PlayerSpecific::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UI_Map_TransformHintArrow_PlayerSpecific::Exec(ScriptContext& context) {
    int offset = (m_InputVariant != 0) ? 3 : 2;
    ScriptVar* input = context.m_ppVars[context.m_InputIndex - 1];
    DoTransform(context, context.GetVarABS(input->m_Id + offset)->m_pSource->m_PlayerIndex, m_InputVariant);
    return ACTION_FINISHED;
}
