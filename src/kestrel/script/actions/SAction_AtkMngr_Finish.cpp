#include "kestrel/script/actions/SAction_AtkMngr_Finish.h"

template <class T>
class WeakPtr {
public:
    T* m_pObject;
};

class cAttackManager {};

const char* SAction_AtkMngr_Finish::GetName() const {
    return "Finish";
}

ActionState SAction_AtkMngr_Finish::DoExec(WeakPtr<cAttackManager>& attackManager, ScriptContext&) {
    ((char*)attackManager.m_pObject)[0x6d0a] = 1;
    return ACTION_FINISHED;
}

void SAction_AtkMngr_Finish::GetInputs(SCmdParams& params) const {
    params.AddParam(SV_ATTACK_MANAGER);
}

void SAction_AtkMngr_Finish::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
