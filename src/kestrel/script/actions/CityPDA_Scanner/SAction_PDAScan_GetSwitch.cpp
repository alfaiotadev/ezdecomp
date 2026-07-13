#include "kestrel/script/actions/CityPDA_Scanner/SAction_PDAScan_GetSwitch.h"

struct ScriptContext;
class Gizmo;
class LegoGizmoScriptVariable;
class CityPDA_ScannerMode;

class CityPDA_Scanner {
public:
    static CityPDA_Scanner* GetFromScriptContext(ScriptContext& context, int);
    CityPDA_ScannerMode* GetActiveProcessor();
    Gizmo* GetSourceControlSwitch();
};

class CityPDA_ScannerMode {
public:
    bool HasActiveControlJob();
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

const char* SAction_PDAScan_GetSwitch::GetName() const {
    return "PDAScan_GetSwitch";
}
void SAction_PDAScan_GetSwitch::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_PDAScan_GetSwitch::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_GIZMO);
}

ActionState SAction_PDAScan_GetSwitch::Exec(ScriptContext& context) {
    CityPDA_Scanner* scanner = CityPDA_Scanner::GetFromScriptContext(context, 0);
    if (scanner != nullptr) {
        Gizmo* gizmo = nullptr;
        CityPDA_ScannerMode* processor = scanner->GetActiveProcessor();
        if (processor != nullptr && processor->HasActiveControlJob()) {
            gizmo = scanner->GetSourceControlSwitch();
        }
        context.SetReturn<LegoGizmoScriptVariable, Gizmo*>(0, gizmo);
    }
    return ACTION_FINISHED;
}
