#include "kestrel/script/actions/SAction_AtkMngr_DisallowAttacks.h"

template <class T>
class WeakPtr {
public:
    T* m_pObject;
};

class cAttackManager {};

const char* SAction_AtkMngr_DisallowAttacks::GetName() const {
    return "DisallowAttacks";
}

ActionState SAction_AtkMngr_DisallowAttacks::DoExec(WeakPtr<cAttackManager>& attackManager, ScriptContext&) {
    ((char*)attackManager.m_pObject)[0x6d0f] = 0;
    return ACTION_FINISHED;
}

void SAction_AtkMngr_DisallowAttacks::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
