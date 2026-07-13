#include "kestrel/script/actions/SAction_UI_HideLevelSummaryScreen.h"

const char* SAction_UI_HideLevelSummaryScreen::GetName() const {
    return "UI_HideLevelSummaryScreen";
}
void SAction_UI_HideLevelSummaryScreen::GetInputs(SCmdParams& params) const {
    params.SanityCheck();
}
void SAction_UI_HideLevelSummaryScreen::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}

class HUDSummaryScreen {
public:
    void Hide();
};

struct LegoCityHudPlayer {
    char pad0[0x80];
    HUDSummaryScreen* m_pSummaryScreen;
    char pad1[0x58];
};

extern int g_playerCount;
extern LegoCityHudPlayer g_pHudPlayerData[];

ActionState SAction_UI_HideLevelSummaryScreen::Exec(ScriptContext& context) {
    for (int i = 0; i < g_playerCount; i++) {
        HUDSummaryScreen* screen = g_pHudPlayerData[i].m_pSummaryScreen;
        if (screen != nullptr) {
            screen->Hide();
        }
    }
    return ACTION_FINISHED;
}
