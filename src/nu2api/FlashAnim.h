#pragma once

struct FlashAnim {
    char* name;
    char _pad[16];
    float length;
};

char* FlashAnim_GetName(FlashAnim* anim);
float FlashAnim_GetLength(FlashAnim* anim);
