#include "kestrel/script/actions/CityPDA_Scanner/SAction_PDAScan_SetZoom.h"

#include <math.h>

struct ScriptContext;

class CityPDA_ScannerCore {
public:
    class CameraController {
    public:
        void SetUserZoomLevel(float);
    };
};

class CityPDA_Scanner {
public:
    static CityPDA_Scanner* GetFromActiveJobScriptContext(ScriptContext& context);
    CityPDA_ScannerCore::CameraController* GetCameraController();
};

struct SVarFloat {
    char pad[0x20];
    float m_Value;
};

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarFloat* GetVarABS(int id) const;
};

const char* SAction_PDAScan_SetZoom::GetName() const {
    return "PDAScan_SetZoom";
}
void SAction_PDAScan_SetZoom::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER);
}
void SAction_PDAScan_SetZoom::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState SAction_PDAScan_SetZoom::Exec(ScriptContext& context) {
    CityPDA_Scanner* scanner = CityPDA_Scanner::GetFromActiveJobScriptContext(context);
    if (scanner != nullptr) {
        float zoom = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id)->m_Value;
        zoom = fminf(zoom, 1.0f);
        zoom = (zoom < 0.0f) ? 0.0f : zoom;
        scanner->GetCameraController()->SetUserZoomLevel(zoom);
    }
    return ACTION_FINISHED;
}
