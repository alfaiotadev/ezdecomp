#include "nucore/nucore.h"

#include "nn/oe.h"
#include "nn/settings.h"

void NuLanguageInitPS(NuLanguage* out_lang, NuRegion* out_region) {
    *out_region = NuRegion::AMERICA;
    nn::settings::LanguageCode system_lang = nn::oe::GetDesiredLanguage();

    using namespace nn::settings;

    if (Language_Japanese == system_lang) {
        *out_lang = NuLanguage::JAPANESE;
    } else if (Language_English == system_lang) {
        *out_lang = NuLanguage::AMERICAN;
    } else if (Language_French == system_lang) {
        *out_lang = NuLanguage::FRENCH;
    } else if (Language_CanadianFrench == system_lang) {
        *out_lang = NuLanguage::FRENCH_CANADIAN;
    } else if (Language_Spanish == system_lang) {
        *out_lang = NuLanguage::SPANISH;
    } else if (Language_German == system_lang) {
        *out_lang = NuLanguage::GERMAN;
    } else if (Language_Italian == system_lang) {
        *out_lang = NuLanguage::ITALIAN;
    } else if (Language_Dutch == system_lang) {
        *out_lang = NuLanguage::DUTCH;
    } else if (Language_Portuguese == system_lang) {
        if (*out_region == NuRegion::AMERICA) {
            *out_lang = NuLanguage::BRAZILIAN_PORTUGUESE;
        } else {
            *out_lang = NuLanguage::PORTUGUESE;
        }
    } else if (Language_Russian == system_lang) {
        *out_lang = NuLanguage::RUSSIAN;
    } else if (Language_Korean == system_lang) {
        *out_lang = NuLanguage::KOREAN;
    } else if (Language_Chinese == system_lang) {
        *out_lang = NuLanguage::CHINESE_SIMPLIFIED;
    } else if (Language_Taiwanese == system_lang) {
        *out_lang = NuLanguage::CHINESE_TRADITIONAL;
    } else if (Language_BritishEnglish == system_lang) {
        *out_lang = NuLanguage::ENGLISH;
    } else if (Language_LatinAmericanSpanish == system_lang) {
        *out_lang = NuLanguage::LATIN_AMERICAN_SPANISH;
    } else {
        *out_lang = NuLanguage::ENGLISH;
    }
}
bool NuLanguageConsoleSelectable(bool* availableLangs) {
    if (availableLangs[10]) {
        return false;
    }
    return !availableLangs[16];
}
