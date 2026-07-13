#include "nu2api/FlashAnim.h"

char* FlashAnim_GetName(FlashAnim* anim) {
    return anim->name;
}

float FlashAnim_GetLength(FlashAnim* anim) {
    return anim->length;
}
