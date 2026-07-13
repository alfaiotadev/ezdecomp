#include "kestrel/script/actions/VehicleAction_SetCanRamp.h"

#include <cstdint>

struct ScriptVar {
    char pad[0x1c];
    int m_Id;
};

struct SVarBool {
    char pad[0x20];
    unsigned char m_Value;
};

struct ScriptContext {
    char pad[0x50];
    ScriptVar** m_ppVars;
    char pad2;
    unsigned char m_InputIndex;
    SVarBool* GetVarABS(int id) const;
};

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    void EnableRamping();
    void DisableRamping();
};

ActionState VehicleAction_SetCanRamp::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    unsigned char canRamp = context.GetVarABS(context.m_ppVars[context.m_InputIndex - 1]->m_Id + 1)->m_Value;
    if (pVehicle != nullptr) {
        void* pUserData = pVehicle->GetGameUserData();
        if (pUserData != nullptr) {
            uintptr_t pGeneric = (uintptr_t)pUserData - 0x10;
            if (pGeneric != 0) {
                if (canRamp != 0) {
                    ((ApiVehicleUserData_LCGeneric*)pGeneric)->EnableRamping();
                } else {
                    ((ApiVehicleUserData_LCGeneric*)pGeneric)->DisableRamping();
                }
            }
        }
    }
    return ACTION_FINISHED;
}
