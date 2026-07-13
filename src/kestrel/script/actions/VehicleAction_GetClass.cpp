#include "kestrel/script/actions/VehicleAction_GetClass.h"

struct CharDef {
    const char* GetName() const;
};

struct VehicleGameData {
    char pad[80];
    CharDef* charDef;
};

struct ApiVehicle {
    char pad[800];
    VehicleGameData* gameData;
};

struct ScriptContext {
    void ReturnText(int, const char*);
};

ActionState VehicleAction_GetClass::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    CharDef* charDef = pVehicle->gameData->charDef;
    const char* name = nullptr;
    if (charDef != nullptr) {
        name = charDef->GetName();
    }
    context.ReturnText(0, name);
    return ACTION_FINISHED;
}
