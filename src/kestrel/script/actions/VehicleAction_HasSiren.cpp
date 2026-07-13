#include "kestrel/script/actions/VehicleAction_HasSiren.h"

struct SVarBool;

struct SirenData {
    char pad[18];
    short sirenIndex;
};

struct VehicleSirenInfo {
    char pad[24];
    SirenData* siren;
};

struct VehicleVariantData {
    char pad[80];
    VehicleSirenInfo* sirenInfo;
};

struct VehicleSubModel {
    char pad[16];
    VehicleVariantData* variantData;
};

struct VehicleModel {
    char pad[592];
    VehicleSubModel* subModel;
};

struct VehicleGameData {
    char pad[80];
    VehicleModel* model;
};

struct ApiVehicle {
    char pad[800];
    VehicleGameData* gameData;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

ActionState VehicleAction_HasSiren::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    bool hasSiren = false;
    SirenData* siren = pVehicle->gameData->model->subModel->variantData->sirenInfo->siren;
    if (siren != nullptr) {
        hasSiren = siren->sirenIndex != -1;
    }
    context.SetReturn<SVarBool, bool>(0, hasSiren);
    return ACTION_FINISHED;
}
