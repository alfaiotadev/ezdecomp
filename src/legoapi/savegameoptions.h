#pragma once

namespace cSplitScreenSegmentInterfaceMgr {
enum class eOptionsSelectedSplitMode;
}

class OPTIONSSAVE {
public:
    unsigned char m_vibration[2];
    // bit 0: surround, 1: vsync, 2: saving, 3: prompts, 4: hintaudio, 5: inverty
    unsigned char m_bitfieldFlags;
    char pad1;
    unsigned char m_sfxVolume;
    unsigned char m_musicVolume;
    unsigned char m_audioVolume;
    unsigned char m_musicOn;
    signed char m_screenX;
    signed char m_screenY;
    unsigned char m_reverseUpdown[2];
    unsigned char m_subtitlesOn;
    unsigned char m_allowAnalytics;
    char pad2[2];
    int m_brightness;
    int m_contrast;
    float m_safeZone;
    cSplitScreenSegmentInterfaceMgr::eOptionsSelectedSplitMode split_screen_mode;
    char pad3[8];

    void CycleOptionsSelectedSplitMode(bool value);
    static int OptionsMaxSize();
    static int OptionsSize();
};