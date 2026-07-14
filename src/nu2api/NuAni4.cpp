#include "nu2api/NuAni4.h"

void NuAni4Swap16(void* p) {
    unsigned char* b = (unsigned char*)p;
    unsigned char tmp = b[0];
    b[0] = b[1];
    b[1] = tmp;
}
