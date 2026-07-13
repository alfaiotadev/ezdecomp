#include "kestrel/script/actions/SAction_UsePedestrians.h"

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
    bool m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    ScriptVar* GetVarABS(int id) const;
};

class CityKrawlies {
public:
    static void PausePedestrianProcessingAndRendering();
    static void ResumePedestrianProcessingAndRendering();
};

const char* SAction_UsePedestrians::GetName() const {
    return "UsePedestrians";
}
void SAction_UsePedestrians::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}
void SAction_UsePedestrians::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_UsePedestrians::Exec(ScriptContext& context) {
    ScriptVar* p = context.m_ppVars[context.m_InputIndex - 1];
    if (context.GetVarABS(p->m_Id)->m_Value) {
        CityKrawlies::ResumePedestrianProcessingAndRendering();
    } else {
        CityKrawlies::PausePedestrianProcessingAndRendering();
    }
    return ACTION_FINISHED;
}
