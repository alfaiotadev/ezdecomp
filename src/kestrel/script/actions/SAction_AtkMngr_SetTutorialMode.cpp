#include "kestrel/script/actions/SAction_AtkMngr_SetTutorialMode.h"

template <class T>
class WeakPtr {
public:
    T* m_pObject;
};

class cAttackManager {};

const char* SAction_AtkMngr_SetTutorialMode::GetName() const {
    return "SetTutorialMode";
}

ActionState SAction_AtkMngr_SetTutorialMode::DoExec(WeakPtr<cAttackManager>& attackManager, ScriptContext&) {
    ((char*)attackManager.m_pObject)[0x6d0c] = 1;
    return ACTION_FINISHED;
}

void SAction_AtkMngr_SetTutorialMode::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
