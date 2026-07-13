#include "kestrel/script/actions/VehicleAction_IsAtTheEndOfSpline.h"

struct SVarBool;

struct ApiVehicle {
    void* GetGameUserData() const;
};

class ApiVehicleUserData_LCGeneric {
public:
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual void Unknown3() = 0;
    virtual void Unknown4() = 0;
    virtual void Unknown5() = 0;
    virtual void Unknown6() = 0;
    virtual void Unknown7() = 0;
    virtual void Unknown8() = 0;
    virtual void Unknown9() = 0;
    virtual void Unknown10() = 0;
    virtual void Unknown11() = 0;
    virtual void Unknown12() = 0;
    virtual void Unknown13() = 0;
    virtual void Unknown14() = 0;
    virtual void Unknown15() = 0;
    virtual void Unknown16() = 0;
    virtual void Unknown17() = 0;
    virtual void Unknown18() = 0;
    virtual void Unknown19() = 0;
    virtual void Unknown20() = 0;
    virtual void Unknown21() = 0;
    virtual void Unknown22() = 0;
    virtual void Unknown23() = 0;
    virtual void Unknown24() = 0;
    virtual void Unknown25() = 0;
    virtual void Unknown26() = 0;
    virtual void Unknown27() = 0;
    virtual void Unknown28() = 0;
    virtual void Unknown29() = 0;
    virtual void Unknown30() = 0;
    virtual void Unknown31() = 0;
    virtual void Unknown32() = 0;
    virtual void Unknown33() = 0;
    virtual void Unknown34() = 0;
    virtual void Unknown35() = 0;
    virtual void Unknown36() = 0;
    virtual void Unknown37() = 0;
    virtual void Unknown38() = 0;
    virtual void Unknown39() = 0;
    virtual int IsAtTheEndOfSpline() = 0;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

VehicleAction_IsAtTheEndOfSpline::~VehicleAction_IsAtTheEndOfSpline() = default;

const char* VehicleAction_IsAtTheEndOfSpline::GetName() const {
    return "IsAtTheEndOfSpline";
}

void VehicleAction_IsAtTheEndOfSpline::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}

void VehicleAction_IsAtTheEndOfSpline::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_NUMBER, "IsAtTheEndOfSpline");
}

ActionState VehicleAction_IsAtTheEndOfSpline::VehicleExec(ApiVehicle* pVehicle, ScriptContext& context) {
    void* pUserData = pVehicle->GetGameUserData();
    ApiVehicleUserData_LCGeneric* pGeneric
        = (pUserData == nullptr) ? nullptr : (ApiVehicleUserData_LCGeneric*)((char*)pUserData - 0x10);
    context.SetReturn<SVarBool, bool>(0, pGeneric->IsAtTheEndOfSpline() & 1);
    return ACTION_FINISHED;
}
