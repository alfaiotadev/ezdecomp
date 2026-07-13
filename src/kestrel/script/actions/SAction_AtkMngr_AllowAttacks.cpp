#include "kestrel/script/actions/SAction_AtkMngr_AllowAttacks.h"

template <class T>
class WeakPtr {
public:
    T* m_pObject;
};

class cAttackManager {};

const char* SAction_AtkMngr_AllowAttacks::GetName() const {
    return "AllowAttacks";
}

ActionState SAction_AtkMngr_AllowAttacks::DoExec(WeakPtr<cAttackManager>& attackManager, ScriptContext&) {
    ((char*)attackManager.m_pObject)[0x6d0f] = 1;
    return ACTION_FINISHED;
}

void SAction_AtkMngr_AllowAttacks::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
