#pragma once

struct FlashFont;

struct FlashElement {
    char* name;
    char pad;
    unsigned char : 6;
    bool enabled : 1;
    unsigned char : 1;
};

char* FlashElement_GetName(FlashElement* element);
bool FlashElement_HasFont(FlashElement* element);
bool FlashElement_IsEnabled(FlashElement* element);
FlashFont* FlashElement_GetFont(FlashElement* element);
