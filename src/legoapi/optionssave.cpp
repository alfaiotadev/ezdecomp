#include "optionssave.h"
#include <algorithm>
#include <cmath>
#include <cstring>

__attribute__((noinline)) void Options::SetBrightness(int param_1) {
    OPTIONSSAVE* puVar2 = options;
    int iVar1;

    if (param_1 > 99) {
        param_1 = 100;
    }

    if (param_1 > -1) {
        iVar1 = param_1;
    } else {
        iVar1 = 0;
    }

    puVar2->m_brightness = iVar1;
    NuVideoSetBrightness(iVar1, puVar2->m_contrast);
}
__attribute__((noinline)) unsigned char Options::GetMusic_on() {
    return options->m_musicOn;
}
__attribute__((noinline)) void Options::SetMusic_on(unsigned char value) {
    options->m_musicOn = value;
}
void Options::SetOptionsSave(OPTIONSSAVE* other) {
    options = other;
}
__attribute__((noinline)) void Options::SetEnglishDialogue_on(bool param1, Options::EApplyLegoSFX param2) {}
Options::Options() {
    options = reinterpret_cast<OPTIONSSAVE*>(this + 1);
}

void Options::AdjustSafeZone(float value) {
    SetSafeZone(GetSafeZone() + value);
}
void Options::AdjustSFX_volume(char value) {
    int sfx_volume = GetSFX_volume();
    int masked = sfx_volume & 0xFF;
    unsigned char new_volume = masked + static_cast<unsigned char>(value);
    if (new_volume < 11) {
        SetSFX_volume(sfx_volume + value);
    }
}
unsigned char Options::GetAllowAnalytics() {
    return options->m_allowAnalytics;
}
__attribute__((noinline)) int Options::GetAudio_volume() {
    int audio_volume = options->m_audioVolume;
    if (audio_volume > 9) {
        audio_volume = 10;
    }
    return audio_volume;
}
__attribute__((noinline)) int Options::GetBrightness() {
    return options->m_brightness;
}
int Options::GetContrast() {
    return options->m_contrast;
}
int Options::GetEnglishDialogue_on() {
    return 0;
}
__attribute__((noinline)) unsigned char Options::GetInvertYAxis() {
    return options->m_bitfieldFlags >> 5 & 1;
}
__attribute__((noinline)) unsigned char Options::GetMusic_volume() {
    return options->m_musicVolume;
}
__attribute__((noinline)) unsigned char Options::GetPrompts() {
    return options->m_bitfieldFlags >> 3 & 1;
}
float Options::GetSafeZone() {
    float value = options->m_safeZone;
    float one = 1.0f;
    float min_value = 0.9f;

    if (value <= one && value < min_value) {
        return one;
    }
    return value;
}
__attribute__((noinline)) int Options::GetSFX_volume() {
    return options->m_sfxVolume;
}
__attribute__((noinline)) unsigned char Options::GetSubtitles_on() {
    return options->m_subtitlesOn;
}
__attribute__((noinline)) unsigned char Options::GetSurround() {
    return options->m_bitfieldFlags & 1;
}
__attribute__((noinline)) unsigned char Options::GetHintAudio_on() {
    return (options->m_bitfieldFlags >> 4) & 1;
}
__attribute__((noinline)) unsigned char Options::GetVibration(int index) {
    return options->m_vibration[index];
}
__attribute__((noinline)) unsigned char Options::GetVSync() {
    return options->m_bitfieldFlags >> 1 & 0x1;
}
Options& Options::operator=(Options& other) {
    OPTIONSSAVE* dst = this->options;
    OPTIONSSAVE* src = other.options;
    memcpy(dst, src, 0x28);
    return *this;
}
__attribute__((noinline)) bool Options::operator==(Options& other) {
    return memcmp(options, other.options, sizeof(OPTIONSSAVE)) == 0;
}
bool Options::operator!=(Options& other) {
    bool result = operator==(other);
    return (~result) & 1;
}
__attribute__((noinline)) void Options::SetVSync(unsigned char value) {
    unsigned char flags = options->m_bitfieldFlags;
    flags = (flags & ~0x2) | (value & 1) << 1;
    options->m_bitfieldFlags = flags;
}
void Options::AdjustBrightness(char value) {
    int brightness = GetBrightness();
    SetBrightness(brightness + value & 0xff);
}
void Options::AdjustMusic_volume(char value) {
    SetMusic_volume(GetMusic_volume() + value);
}
void Options::CycleOptionsSelectedSplitMode(bool value) {
    this->options->CycleOptionsSelectedSplitMode(value);
}
unsigned char Options::GetReverse_updown(int player_index) {
    return options->m_reverseUpdown[player_index];
}
__attribute__((noinline)) unsigned char Options::GetSaving_on() {
    return options->m_bitfieldFlags >> 2 & 1;
}
unsigned char Options::GetScreen_x() {
    return options->m_screenX;
}
unsigned char Options::GetScreen_y() {
    return options->m_screenY;
}
cSplitScreenSegmentInterfaceMgr::eOptionsSelectedSplitMode Options::GetSplitScreenMode() {
    return options->split_screen_mode;
}
void Options::SetAllowAnalytics(bool param1, bool param2) {
    unsigned char* ptr = &options->m_allowAnalytics;
    *ptr = param1 & 1;
}
__attribute__((noinline)) void Options::SetAudio_volume(unsigned char value) {
    Options* self = this;
    if (value > 9) {
        value = 10;
    }
    self->options->m_audioVolume = value;
    // todo missing: LegoSFX::SetMasterBusVolume(value);
}
__attribute__((noinline)) void Options::SetHintAudio_on(unsigned char value) {
    unsigned char flags = options->m_bitfieldFlags;
    flags = (flags & 0xEF) | ((value & 1) << 4);
    options->m_bitfieldFlags = flags;
}
__attribute__((noinline)) void Options::SetInvertYAxis(unsigned char value) {
    unsigned char flags = options->m_bitfieldFlags;
    flags = (flags & ~0x20) | (value & 1) << 5;
    options->m_bitfieldFlags = flags;
}
__attribute__((noinline)) void Options::SetMusic_volume(unsigned char value) {
    options->m_musicVolume = value;
}
__attribute__((noinline)) void Options::SetPrompts(unsigned char value) {
    unsigned char flags = options->m_bitfieldFlags;
    flags = (flags & ~0x8) | (value & 1) << 3;
    options->m_bitfieldFlags = flags;
}
void Options::SetReverse_updown(int player_index, unsigned char is_reversed) {
    options->m_reverseUpdown[player_index] = is_reversed;
}
__attribute__((noinline)) void Options::SetSafeZone(float value) {
    float clamped = std::fmin(value, 1.0f);
    if (clamped < 0.9f) {
        clamped = 0.9f;
    }

    options->m_safeZone = clamped;
    SetUISafeZone(clamped);
}
__attribute__((noinline)) void Options::SetSaving_on(unsigned char value) {
    unsigned char flags = options->m_bitfieldFlags;
    flags = (flags & ~0x4) | (value & 1) << 2;
    options->m_bitfieldFlags = flags;
}
void Options::SetScreen_xy(signed char x, signed char y) {
    OPTIONSSAVE* ptr = options;
    ptr->m_screenX = x;
    ptr->m_screenY = y;
}
void Options::SetSplitScreenMode(cSplitScreenSegmentInterfaceMgr::eOptionsSelectedSplitMode mode) {
    options->split_screen_mode = mode;
}
__attribute__((noinline)) void Options::SetSurround(unsigned char value) {
    unsigned char flags = options->m_bitfieldFlags;
    flags = (flags & ~0x1) | (value & 1) << 0;
    options->m_bitfieldFlags = flags;
}
__attribute__((noinline)) void Options::SetVibration(int player_index, unsigned char value) {
    options->m_vibration[player_index] = value;
}
void Options::ToggleHintAudio_on() {
    SetHintAudio_on(GetHintAudio_on() == 0);
}
void Options::ToggleInvertYAxis() {
    SetInvertYAxis(GetInvertYAxis() == 0);
}
void Options::ToggleMusic_on() {
    SetMusic_on(GetMusic_on() == 0);
}
void Options::TogglePrompts() {
    SetPrompts(GetPrompts() == 0);
}
void Options::ToggleReverse_updown(int player_index) {
    SetReverse_updown(player_index, GetReverse_updown(player_index) == 0);
}
void Options::ToggleSaving_on() {
    SetSaving_on(GetSaving_on() == 0);
}
void Options::ToggleSubtitles_on() {
    SetSubtitles_on(GetSubtitles_on() == 0);
}
__attribute__((noinline)) void Options::SetSubtitles_on(unsigned char value) {
    options->m_subtitlesOn = value;
}
__attribute__((noinline)) void Options::ToggleSurround() {
    SetSurround(GetSurround() == 0);
}
void Options::ToggleVibration(int value) {
    SetVibration(value, GetVibration(value) == 0);
}
__attribute__((noinline)) void Options::SetSFX_volume(unsigned char value) {
    options->m_sfxVolume = value;
}
void Options::ToggleVSync() {
    SetVSync(GetVSync() == 0);
}
