#include "kestrel/script/actions/SAction_FlowUI_ShowRetryScreen.h"

namespace FlowMissionUI {

class HUDScreenManager {
public:
    void ShowRetryScreen();
};

class ScriptHandler {
public:
    char pad[0x18];
    bool m_RetryScreenEnabled;
    char pad2[0x5F];
    HUDScreenManager* m_pHUDScreenManager;
};

__attribute__((visibility("hidden"))) ScriptHandler* g_pScriptHandler;

}  // namespace FlowMissionUI

const char* FlowMissionUI::SAction_FlowUI_ShowRetryScreen::GetName() const {
    return "FlowUI_ShowRetryScreen";
}
void FlowMissionUI::SAction_FlowUI_ShowRetryScreen::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void FlowMissionUI::SAction_FlowUI_ShowRetryScreen::GetOutputs(SCmdParams& params) const {
    ActionInstanceData::GetOutputs(params);
}

ActionState FlowMissionUI::SAction_FlowUI_ShowRetryScreen::Exec(ScriptContext& context) {
    auto* hud = g_pScriptHandler->m_pHUDScreenManager;
    if (hud != nullptr && g_pScriptHandler->m_RetryScreenEnabled != 0) {
        hud->ShowRetryScreen();
        return ACTION_FINISHED;
    }
    return ACTION_YIELD;
}
