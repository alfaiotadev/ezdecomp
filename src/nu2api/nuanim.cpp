#include "nu2api/nuanim.h"

char nuanim_use_quats_flag;

char NuAnimSetUseQuatsFlag(char flag) {
    char old = nuanim_use_quats_flag;
    nuanim_use_quats_flag = flag;
    return old;
}

char NuAnimGetUseQuatsFlag() {
    return nuanim_use_quats_flag;
}
