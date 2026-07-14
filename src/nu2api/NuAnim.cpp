#include "nu2api/NuAnim.h"

static char* volatile g_useQuatsFlag __attribute__((aligned(4096)));

char NuAnimGetUseQuatsFlag() {
    return *g_useQuatsFlag;
}
