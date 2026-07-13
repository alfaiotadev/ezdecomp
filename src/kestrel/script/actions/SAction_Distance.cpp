#include "kestrel/script/actions/SAction_Distance.h"

#include <math.h>

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarPosition {
    char pad[0x20];
    float m_X;
    float m_Y;
    float m_Z;
};

struct SVarFloat {
    char pad[0x20];
    float m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;

    SVarPosition* GetVarABS(int id) const;
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_Distance::GetName() const {
    return "Distance";
}
void SAction_Distance::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_POSITION);
    params.AddParam(SV_POSITION);
}
void SAction_Distance::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}

ActionState SAction_Distance::Exec(ScriptContext& context) {
    SVarPosition* pPos1 = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id);
    SVarPosition* pPos2 = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1);

    float p1x = pPos1->m_X;
    float p1y = pPos1->m_Y;
    float p1z = pPos1->m_Z;
    float p2x = pPos2->m_X;
    float p2y = pPos2->m_Y;
    float p2z = pPos2->m_Z;

    float dy = p1y - p2y;
    float dx = p1x - p2x;
    float dz = p1z - p2z;

    float sq = (dx * dx + dy * dy) + dz * dz;
    float dist;
    if (sq <= 0.0f) {
        dist = 0.0f;
    } else {
        dist = sqrtf(sq);
    }

    context.SetReturn<SVarFloat, float>(0, dist);
    return ACTION_FINISHED;
}
