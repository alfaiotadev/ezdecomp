#pragma once

#include "kestrel/script/actions/ActionInstanceData.h"

template <class T>
class WeakPtr;
class cAttackManager;

class SAction_AtkMngr_StopAutoSuspend : public ActionInstanceData {
public:
    const char* GetName() const override;
    ActionState DoExec(WeakPtr<cAttackManager>&, ScriptContext&);
    void GetOutputs(SCmdParams& params) const override;
};
