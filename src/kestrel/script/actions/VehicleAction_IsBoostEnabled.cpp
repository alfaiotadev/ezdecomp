#include "kestrel/script/actions/VehicleAction_IsBoostEnabled.h"

struct SVarBool;

struct CHEAT_s {
    char pad[0x20];
};

class LegoCityGame {
public:
    char pad[0x9f0];
    CHEAT_s m_BoostCheat;
};

__attribute__((visibility("hidden"))) extern LegoCityGame* g_pLegoCityGame;
int Cheat_IsOn(CHEAT_s*);

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    char pad[1124];
    bool boostEnabled;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState VehicleAction_IsBoostEnabled::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    bool isBoostEnabled = pGeneric->boostEnabled;
    if (!isBoostEnabled) {
        isBoostEnabled = Cheat_IsOn(&g_pLegoCityGame->m_BoostCheat) != 0;
    }
    context.SetReturn<SVarBool, bool>(0, isBoostEnabled);
    return ACTION_FINISHED;
}
