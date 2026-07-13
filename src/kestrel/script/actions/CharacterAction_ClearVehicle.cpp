#include "kestrel/script/actions/CharacterAction_ClearVehicle.h"

struct ApiCharacter;

struct ClearVehicleParams {
    int field_0;
    char pad[24];
    void* field_32;
    bool field_40;
};

void CharacterAction_ClearVehicle::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

ActionState CharacterAction_ClearVehicle::CharacterExec(ApiCharacter* pCharacter, ScriptContext&) {
    void* p = *(void**)((char*)pCharacter + 768);
    if (p != nullptr) {
        ClearVehicleParams params;
        params.field_0 = 1;
        params.field_32 = nullptr;
        params.field_40 = false;
        void (*fn)(void*, void*) = (void (*)(void*, void*))(*(void***)p)[70];
        fn(p, &params);
    }
    return ACTION_FINISHED;
}
