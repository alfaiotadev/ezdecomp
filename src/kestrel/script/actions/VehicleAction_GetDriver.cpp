#include "kestrel/script/actions/VehicleAction_GetDriver.h"

struct ApiCharacter;
struct ApiCharacterScriptVariable;

struct VehicleDefSeat {
    enum SEATTYPES {
        kDriver = 1,
    };
};

struct ApiVehicle {
    ApiCharacter* GetSeatOccupant(VehicleDefSeat::SEATTYPES);
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState VehicleAction_GetDriver::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    ApiCharacter* driver = nullptr;
    if (pVehicle != nullptr) {
        driver = pVehicle->GetSeatOccupant(VehicleDefSeat::kDriver);
    }
    context.SetReturn<ApiCharacterScriptVariable, ApiCharacter*>(0, driver);
    return ACTION_FINISHED;
}
