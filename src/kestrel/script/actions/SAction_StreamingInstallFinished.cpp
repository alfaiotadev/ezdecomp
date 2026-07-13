#include "kestrel/script/actions/SAction_StreamingInstallFinished.h"

struct SVarBool;
struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

class FrameworkImposeCommonErrors {
public:
    static int GetStreamingInstallProgress();
};

const char* SAction_StreamingInstallFinished::GetName() const {
    return "StreamingInstallFinished";
}
void SAction_StreamingInstallFinished::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_StreamingInstallFinished::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_StreamingInstallFinished::Exec(ScriptContext& context) {
    if (FrameworkImposeCommonErrors::GetStreamingInstallProgress() <= 99) {
        context.SetReturn<SVarBool, bool>(0, false);
    } else {
        context.SetReturn<SVarBool, bool>(0, true);
    }
    return ACTION_FINISHED;
}
