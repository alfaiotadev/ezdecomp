#pragma once
#include "legoapi/savegameoptions.h"

class EdStream;
void NuVideoSetBrightness(int brightness, int param_2);
void SetUISafeZone(float param_1);

class Options {
    OPTIONSSAVE* options;
    enum class EApplyLegoSFX;

public:
    Options();

    Options& operator=(Options& other);
    bool operator!=(Options& other);
    bool operator==(Options& value);

    void AdjustAudio_volume(char value);
    void AdjustBrightness(char value);
    void AdjustMusic_volume(char value);
    void AdjustSafeZone(float value);
    void AdjustSFX_volume(char value);
    void CycleOptionsSelectedSplitMode(bool value);
    unsigned char GetAllowAnalytics();
    int GetAudio_volume();
    int GetBrightness();
    int GetContrast();
    int GetEnglishDialogue_on();
    unsigned char GetHintAudio_on();
    unsigned char GetInvertYAxis();
    unsigned char GetMusic_on();
    unsigned char GetMusic_volume();
    unsigned char GetPrompts();
    unsigned char GetReverse_updown(int value);
    float GetSafeZone();
    unsigned char GetSaving_on();
    unsigned char GetScreen_x();
    unsigned char GetScreen_y();
    int GetSFX_volume();
    cSplitScreenSegmentInterfaceMgr::eOptionsSelectedSplitMode GetSplitScreenMode();
    unsigned char GetSubtitles_on();
    unsigned char GetSurround();

    unsigned char GetVibration(int value);
    unsigned char GetVSync();
    void Serialise(EdStream* value);  // todo implement
    void SetAllowAnalytics(bool param1, bool param2);
    void SetAudio_volume(unsigned char value);
    void SetBrightness(int value);
    void SetEnglishDialogue_on(bool param1, EApplyLegoSFX param2);
    void SetHintAudio_on(unsigned char value);
    void SetInvertYAxis(unsigned char value);
    void SetMusic_on(unsigned char value);
    void SetMusic_volume(unsigned char value);
    void SetOptionsSave(OPTIONSSAVE* value);
    void SetPrompts(unsigned char value);
    void SetReverse_updown(int player_index, unsigned char is_reversed);

    void SetSafeZone(float value);
    void SetSaving_on(unsigned char value);
    void SetScreen_xy(signed char x, signed char y);
    void SetSFX_volume(unsigned char value);
    void SetSplitScreenMode(cSplitScreenSegmentInterfaceMgr::eOptionsSelectedSplitMode param_2);
    void SetSurround(unsigned char enable_surround);
    void SetVibration(int player_index, unsigned char value);
    void SetVSync(unsigned char value);
    void ToggleHintAudio_on();
    void ToggleInvertYAxis();
    void ToggleMusic_on();
    void TogglePrompts();
    void ToggleReverse_updown(int value);
    void ToggleSaving_on();
    void ToggleSubtitles_on();
    void SetSubtitles_on(unsigned char value);
    void ToggleSurround();
    void ToggleVibration(int value);
    void ToggleVSync();
};
