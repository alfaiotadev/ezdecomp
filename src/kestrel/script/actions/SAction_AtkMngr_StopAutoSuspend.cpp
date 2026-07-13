#include "kestrel/script/actions/SAction_AtkMngr_StopAutoSuspend.h"

template <class T>
class WeakPtr {
public:
    T* m_pObject;
};

class cAttackManager {};

const char* SAction_AtkMngr_StopAutoSuspend::GetName() const {
    return "StopAutoSuspend";
}

ActionState SAction_AtkMngr_StopAutoSuspend::DoExec(WeakPtr<cAttackManager>& attackManager, ScriptContext&) {
    ((char*)attackManager.m_pObject)[0x6d10] = 0;
    return ACTION_FINISHED;
}

void SAction_AtkMngr_StopAutoSuspend::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
