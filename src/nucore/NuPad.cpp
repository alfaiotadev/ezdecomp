#include "nn/types.h"

class NuPadSystem {
public:
    __attribute__((visibility("hidden"))) static char ms_NuPadSignOutWarningEvent[0x131];
};

__attribute__((visibility("hidden"))) char NuPadSystem::ms_NuPadSignOutWarningEvent[0x131];

__attribute__((naked)) void NuPadSysUIDismissed() {
    __asm__ volatile("adrp x8, %0\n"
                     "orr w9, wzr, #0x1\n"
                     "strb w9, [x8, #296]\n"
                     "ret"
                     :
                     : "i"(&NuPadSystem::ms_NuPadSignOutWarningEvent[8])
                     : "x8", "x9", "memory");
}
