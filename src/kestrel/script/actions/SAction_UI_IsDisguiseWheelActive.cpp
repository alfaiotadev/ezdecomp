#include "kestrel/script/actions/SAction_UI_IsDisguiseWheelActive.h"

struct SVarBool;

class CityPDA_CharacterShop {
public:
    bool IsActive();
};

class CityPDASystem_ShopContainer {
public:
    char pad[0x15e8];
    CityPDA_CharacterShop* m_pCharacterShop;
};

class CityPDASystem {
public:
    CityPDASystem* bodge_GetActiveManager();
    char pad[0x1728];
    CityPDASystem_ShopContainer* m_pShopContainer;
};

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

__attribute__((visibility("hidden"))) CityPDASystem** g_ppCityPDASystem;

const char* SAction_UI_IsDisguiseWheelActive::GetName() const {
    return "UI_IsDisguiseWheelActive";
}
void SAction_UI_IsDisguiseWheelActive::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_IsDisguiseWheelActive::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
    params.AddParam(SV_BOOL);
}

ActionState SAction_UI_IsDisguiseWheelActive::Exec(ScriptContext& context) {
    CityPDASystem* pActive = (*g_ppCityPDASystem)->bodge_GetActiveManager();
    bool active = pActive && pActive->m_pShopContainer->m_pCharacterShop->IsActive();
    context.SetReturn<SVarBool, bool>(0, active);
    return ACTION_FINISHED;
}
